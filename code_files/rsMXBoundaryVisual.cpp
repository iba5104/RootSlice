#include "rsMXBoundaryVisual.h"
#include "globals.h"

/////////////////////////////////////////////// MXBoundaryCellVisual ///////////////////////////////////////////
void rsMXBoundaryVisual::MXBoundaryCellVisual
(rsMXBoundaryOutDB* RsMXBoundaryOutDB,
	vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
	map<int, vector< vector <vector<double> > > >::iterator itMap;
	vector< vector <vector<double> > >::iterator itVec3;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int iRingNum;
	int cellNum;
	int sliceTempNum;

	int MXBoundaryCellNum = 0;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "MXBoundaryCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("MXBoundaryCell.vtp");


	ofstream fout(getFolderName() + "staticNum.txt", ios::app);

	//fout << "MXBoundaryCellVisual" << endl;
	/// Right Up;

	//fout << "Right Up" << endl;
	for (itMap = RsMXBoundaryOutDB->boundaryCellRightUpObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->boundaryCellRightUpObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec3 = (*itMap).second.begin(), iRingNum = 0;
			itVec3 != (*itMap).second.end();
			itVec3++, iRingNum++)
		{
			for (itVec2 = (*itVec3).begin(), cellNum = 0;
				itVec2 != (*itVec3).end();
				itVec2++, cellNum++)
			{
				for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
					itVec1 != (*itVec2).end();
					sliceTempNum++, itVec1++)
				{
					vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
						= vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

					vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
						= vtkSmartPointer<vtkParametricFunctionSource>::New();

					vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
						= vtkSmartPointer<vtkPolyDataMapper>::New();

					vtkSmartPointer<vtkActor> actor
						= vtkSmartPointer<vtkActor>::New();

					superEllipsoid->SetXRadius
					(RsMXBoundaryOutDB->boundaryUpCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->boundaryUpCellObjectParallelDB[i][iRingNum]);
					/// Right Up;
					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->boundaryCellRightUpObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsMXBoundaryOutDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsMXBoundaryOutDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsMXBoundaryOutDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 5 );
							(numSequence, 0.5);
					}
					polydata->GetPointData()->SetScalars(scalars);


					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsMXBoundaryOutDB->boundaryCellRightUpXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->boundaryCellRightUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->boundaryCellRightUpYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum]);
					trans->RotateX(90);

					transFilter->SetInputData(polydata);
					transFilter->SetTransform(trans);

					/// Add transFilter to vtkAppendPolyData pointer everytime;
					append->AddInputConnection(transFilter->GetOutputPort());

					/// vtkPolyDataMapper and vtkActor;
					polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
					actor->SetMapper(polyDataMapper);

					//               polyDataMapper->SetInputConnection
					//               ( superEllipsoidFunction->GetOutputPort() );
					//
					//
					//               actor->SetMapper( polyDataMapper );
					//
					//               /// Right Up;
					////               fout << "Before RotateY" << endl;
					//               actor->RotateY
					//               ( RsMXBoundaryOutDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "After RotateY" << endl;
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsMXBoundaryOutDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->boundaryCellRightUpXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->boundaryCellRightUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->boundaryCellRightUpYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryCellNum += 1;
				}
			}
		}
	}


	/// Left Up;
	//fout << "Left Up" << endl;
	for (itMap = RsMXBoundaryOutDB->boundaryCellLeftUpObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->boundaryCellLeftUpObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec3 = (*itMap).second.begin(), iRingNum = 0;
			itVec3 != (*itMap).second.end();
			itVec3++, iRingNum++)
		{
			for (itVec2 = (*itVec3).begin(), cellNum = 0;
				itVec2 != (*itVec3).end();
				itVec2++, cellNum++)
			{
				for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
					itVec1 != (*itVec2).end();
					sliceTempNum++, itVec1++)
				{
					vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
						= vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

					vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
						= vtkSmartPointer<vtkParametricFunctionSource>::New();

					vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
						= vtkSmartPointer<vtkPolyDataMapper>::New();

					vtkSmartPointer<vtkActor> actor
						= vtkSmartPointer<vtkActor>::New();

					superEllipsoid->SetXRadius
					(RsMXBoundaryOutDB->boundaryUpCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->boundaryUpCellObjectParallelDB[i][iRingNum]);
					/// Left Up;
					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->boundaryCellLeftUpObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsMXBoundaryOutDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsMXBoundaryOutDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsMXBoundaryOutDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 5 );
							(numSequence, 0.5);
					}
					polydata->GetPointData()->SetScalars(scalars);


					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsMXBoundaryOutDB->boundaryCellLeftUpXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->boundaryCellLeftUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->boundaryCellLeftUpYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum]);
					trans->RotateX(90);

					transFilter->SetInputData(polydata);
					transFilter->SetTransform(trans);

					/// Add transFilter to vtkAppendPolyData pointer everytime;
					append->AddInputConnection(transFilter->GetOutputPort());

					/// vtkPolyDataMapper and vtkActor;
					polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
					actor->SetMapper(polyDataMapper);

					//               polyDataMapper->SetInputConnection
					//               ( superEllipsoidFunction->GetOutputPort() );
					//
					//
					//               actor->SetMapper( polyDataMapper );
					//
					//               actor->RotateY
					//               ( RsMXBoundaryOutDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "LeftUpCenterRadianDB: "
					////                    << RsMXBoundaryOutDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->boundaryCellLeftUpXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->boundaryCellLeftUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->boundaryCellLeftUpYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryCellNum += 1;
				}
			}
		}
	}

	/// Right Down;
 //   fout << "Right Down" << endl;
	for (itMap = RsMXBoundaryOutDB->boundaryCellRightDownObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->boundaryCellRightDownObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec3 = (*itMap).second.begin(), iRingNum = 0;
			itVec3 != (*itMap).second.end();
			itVec3++, iRingNum++)
		{
			for (itVec2 = (*itVec3).begin(), cellNum = 0;
				itVec2 != (*itVec3).end();
				itVec2++, cellNum++)
			{
				for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
					itVec1 != (*itVec2).end();
					sliceTempNum++, itVec1++)
				{
					vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
						= vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

					vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
						= vtkSmartPointer<vtkParametricFunctionSource>::New();

					vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
						= vtkSmartPointer<vtkPolyDataMapper>::New();

					vtkSmartPointer<vtkActor> actor
						= vtkSmartPointer<vtkActor>::New();


					superEllipsoid->SetXRadius
					(RsMXBoundaryOutDB->boundaryDownCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->boundaryDownCellObjectParallelDB[i][iRingNum]);
					/// Right Down;
					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->boundaryCellRightDownObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsMXBoundaryOutDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsMXBoundaryOutDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsMXBoundaryOutDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 5 );
							(numSequence, 0.5);
					}
					polydata->GetPointData()->SetScalars(scalars);


					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsMXBoundaryOutDB->boundaryCellRightDownXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->boundaryCellRightDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->boundaryCellRightDownYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum]);
					trans->RotateX(90);

					transFilter->SetInputData(polydata);
					transFilter->SetTransform(trans);

					/// Add transFilter to vtkAppendPolyData pointer everytime;
					append->AddInputConnection(transFilter->GetOutputPort());

					/// vtkPolyDataMapper and vtkActor;
					polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
					actor->SetMapper(polyDataMapper);

					//               polyDataMapper->SetInputConnection
					//               ( superEllipsoidFunction->GetOutputPort() );
					//
					//
					//               actor->SetMapper( polyDataMapper );
					//
					//               /// Right Down;
					//
					//               actor->RotateY
					//               ( RsMXBoundaryOutDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsMXBoundaryOutDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->boundaryCellRightDownXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->boundaryCellRightDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->boundaryCellRightDownYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryCellNum += 1;
				}
			}
		}
	}

	/// Left Down;

 //   fout << "Left Down" << endl;
	for (itMap = RsMXBoundaryOutDB->boundaryCellLeftDownObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->boundaryCellLeftDownObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec3 = (*itMap).second.begin(), iRingNum = 0;
			itVec3 != (*itMap).second.end();
			itVec3++, iRingNum++)
		{
			for (itVec2 = (*itVec3).begin(), cellNum = 0;
				itVec2 != (*itVec3).end();
				itVec2++, cellNum++)
			{
				for (sliceTempNum = 0, itVec1 = (*itVec2).begin();
					itVec1 != (*itVec2).end();
					sliceTempNum++, itVec1++)
				{
					vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
						= vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

					vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
						= vtkSmartPointer<vtkParametricFunctionSource>::New();

					vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
						= vtkSmartPointer<vtkPolyDataMapper>::New();

					vtkSmartPointer<vtkActor> actor
						= vtkSmartPointer<vtkActor>::New();

					superEllipsoid->SetXRadius
					(RsMXBoundaryOutDB->boundaryDownCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->boundaryDownCellObjectParallelDB[i][iRingNum]);
					/// Left Down;
					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->boundaryCellLeftDownObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsMXBoundaryOutDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsMXBoundaryOutDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsMXBoundaryOutDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 5 );
							(numSequence, 0.5);
					}
					polydata->GetPointData()->SetScalars(scalars);


					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsMXBoundaryOutDB->boundaryCellLeftDownXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->boundaryCellLeftDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->boundaryCellLeftDownYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum]);
					trans->RotateX(90);

					transFilter->SetInputData(polydata);
					transFilter->SetTransform(trans);

					/// Add transFilter to vtkAppendPolyData pointer everytime;
					append->AddInputConnection(transFilter->GetOutputPort());

					/// vtkPolyDataMapper and vtkActor;
					polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
					actor->SetMapper(polyDataMapper);

					//               polyDataMapper->SetInputConnection
					//               ( superEllipsoidFunction->GetOutputPort() );
					//
					//
					//               actor->SetMapper( polyDataMapper );
					//
					//               /// Left Down;
					//
					//               actor->RotateY
					//               ( RsMXBoundaryOutDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsMXBoundaryOutDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->boundaryCellLeftDownXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->boundaryCellLeftDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->boundaryCellLeftDownYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryCellNum += 1;
				}
			}
		}
	}
	fout << "MXBoundaryCellNum: " << MXBoundaryCellNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}