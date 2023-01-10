#include "rsPXBoundaryVisual.h"
#include "globals.h"

/////////////////////////////////////////////// PXBoundaryCellVisual ///////////////////////////////////////////
void rsPXBoundaryVisual::BoundaryCellVisual
(rsPXBoundaryDB* RsPXBoundaryDB,
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

	int PXBoundaryCellNum = 0;

	ofstream fout(getFolderName() + "staticNum.txt", ios::app);

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "PXBoundary.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("PXBoundary.vtp");

	/// Right Up;

 //   fout << "Right Up" << endl;
	for (itMap = RsPXBoundaryDB->boundaryCellRightUpObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->boundaryCellRightUpObjectHeightDB.end();
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
					(RsPXBoundaryDB->boundaryUpCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsPXBoundaryDB->boundaryUpCellObjectParallelDB[i][iRingNum]);
					/// Right Up;
					superEllipsoid->SetZRadius
					(RsPXBoundaryDB->boundaryCellRightUpObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPXBoundaryDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPXBoundaryDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPXBoundaryDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkFloatArray* scalars = vtkFloatArray::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 6 );
							(numSequence, 0.8);

					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPXBoundaryDB->boundaryCellRightUpXDB[i][iRingNum][cellNum],
						RsPXBoundaryDB->boundaryCellRightUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPXBoundaryDB->boundaryCellRightUpYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPXBoundaryDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               actor->SetMapper( polyDataMapper );
					//
					//               actor->RotateY
					//               ( RsPXBoundaryDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum] );
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPXBoundaryDB->boundaryCellRightUpXDB[i][iRingNum][cellNum],
					//                 RsPXBoundaryDB->boundaryCellRightUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPXBoundaryDB->boundaryCellRightUpYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

					renL->AddActor(actor);
					PXBoundaryCellNum += 1;

				}
			}
		}
	}


	/// Left Up;
 //   fout << "Left Up" << endl;
	for (itMap = RsPXBoundaryDB->boundaryCellLeftUpObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->boundaryCellLeftUpObjectHeightDB.end();
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
					(RsPXBoundaryDB->boundaryUpCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsPXBoundaryDB->boundaryUpCellObjectParallelDB[i][iRingNum]);
					/// Left Up;
					superEllipsoid->SetZRadius
					(RsPXBoundaryDB->boundaryCellLeftUpObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPXBoundaryDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPXBoundaryDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPXBoundaryDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkFloatArray* scalars = vtkFloatArray::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 6 );
							(numSequence, 0.8);
					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPXBoundaryDB->boundaryCellLeftUpXDB[i][iRingNum][cellNum],
						RsPXBoundaryDB->boundaryCellLeftUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPXBoundaryDB->boundaryCellLeftUpYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPXBoundaryDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum]);
					trans->RotateX(90);

					transFilter->SetInputData(polydata);
					transFilter->SetTransform(trans);

					/// Add transFilter to vtkAppendPolyData pointer everytime;
					append->AddInputConnection(transFilter->GetOutputPort());

					/// vtkPolyDataMapper and vtkActor;
					polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
					actor->SetMapper(polyDataMapper);

					//               ( superEllipsoidFunction->GetOutputPort() );
					//
					//
					//               actor->SetMapper( polyDataMapper );
					//
					//               /// Left Up;
					//
					//               actor->RotateY
					//               ( RsPXBoundaryDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "LeftUpCenterRadianDB: "
					////                    << RsPXBoundaryDB->boundaryCellLeftUpCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPXBoundaryDB->boundaryCellLeftUpXDB[i][iRingNum][cellNum],
					//                 RsPXBoundaryDB->boundaryCellLeftUpObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPXBoundaryDB->boundaryCellLeftUpYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

					renL->AddActor(actor);
					PXBoundaryCellNum += 1;

				}
			}
		}
	}

	/// Right Down;

 //   fout << "Right Down" << endl;
	for (itMap = RsPXBoundaryDB->boundaryCellRightDownObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->boundaryCellRightDownObjectHeightDB.end();
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
					(RsPXBoundaryDB->boundaryDownCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsPXBoundaryDB->boundaryDownCellObjectParallelDB[i][iRingNum]);
					/// Right Down;
					superEllipsoid->SetZRadius
					(RsPXBoundaryDB->boundaryCellRightDownObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPXBoundaryDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPXBoundaryDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPXBoundaryDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkFloatArray* scalars = vtkFloatArray::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 6 );
							(numSequence, 0.8);
					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPXBoundaryDB->boundaryCellRightDownXDB[i][iRingNum][cellNum],
						RsPXBoundaryDB->boundaryCellRightDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPXBoundaryDB->boundaryCellRightDownYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPXBoundaryDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               actor->SetMapper( polyDataMapper );
					//
					//               /// Right Down;
					//
					//               actor->RotateY
					//               ( RsPXBoundaryDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsPXBoundaryDB->boundaryCellRightDownCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPXBoundaryDB->boundaryCellRightDownXDB[i][iRingNum][cellNum],
					//                 RsPXBoundaryDB->boundaryCellRightDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPXBoundaryDB->boundaryCellRightDownYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

					renL->AddActor(actor);
					PXBoundaryCellNum += 1;

				}
			}
		}
	}

	/// Left Down;

 //   fout << "Left Down" << endl;
	for (itMap = RsPXBoundaryDB->boundaryCellLeftDownObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->boundaryCellLeftDownObjectHeightDB.end();
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
					(RsPXBoundaryDB->boundaryDownCellObjectVerticalDB[i]);

					superEllipsoid->SetYRadius
					(RsPXBoundaryDB->boundaryDownCellObjectParallelDB[i][iRingNum]);
					/// Left Down;
					superEllipsoid->SetZRadius
					(RsPXBoundaryDB->boundaryCellLeftDownObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPXBoundaryDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPXBoundaryDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPXBoundaryDB->wResolution);

					/// You need to update() if you want to output the data of object;
					superEllipsoidFunction->Update();

					/// Set Scalars;
					// Extract the polydata
					vtkSmartPointer<vtkPolyData> polydata =
						vtkSmartPointer<vtkPolyData>::New();
					polydata = superEllipsoidFunction->GetOutput();

					int pointNum;
					pointNum = polydata->GetNumberOfPoints();

					vtkFloatArray* scalars = vtkFloatArray::New();
					scalars->SetName("Color");
					int numSequence;

					/// Add scalar to point;
					for (numSequence = 0; numSequence < pointNum; numSequence++)
					{
						scalars->InsertTuple1
							//                  ( numSequence, double(sliceTempNum) / 6 );
							(numSequence, 0.8);
					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPXBoundaryDB->boundaryCellLeftDownXDB[i][iRingNum][cellNum],
						RsPXBoundaryDB->boundaryCellLeftDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPXBoundaryDB->boundaryCellLeftDownYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPXBoundaryDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               actor->SetMapper( polyDataMapper );
					//               /// Left Down;
					//
					//               actor->RotateY
					//               ( RsPXBoundaryDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsPXBoundaryDB->boundaryCellLeftDownCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPXBoundaryDB->boundaryCellLeftDownXDB[i][iRingNum][cellNum],
					//                 RsPXBoundaryDB->boundaryCellLeftDownObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPXBoundaryDB->boundaryCellLeftDownYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
					//                 RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

					renL->AddActor(actor);
					PXBoundaryCellNum += 1;

				}
			}
		}
	}
	fout << "PXBoundaryCellNum: " << PXBoundaryCellNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}