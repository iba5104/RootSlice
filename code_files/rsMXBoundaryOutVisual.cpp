#include "rsMXBoundaryOutVisual.h"


/////////////////////////////////////////////// MXBoundaryInterCellVisual ///////////////////////////////////////////
void rsMXBoundaryOutVisual::MXBoundaryInterCellVisual
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

	int MXBoundaryOutCellNum = 0;

	ofstream fout("staticNum.txt", ios::app);

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();

	writer->SetFileName("MXBoundaryInterCell.vtp");

	for (itMap = RsMXBoundaryOutDB->interCellObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->interCellObjectHeightDB.end();
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
					(RsMXBoundaryOutDB->interVerticalLengthHalfDB[iRingNum]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->interParallelLengthHalfDB[i][iRingNum]);

					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->interCellObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

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

					trans->Translate(RsMXBoundaryOutDB->interCellXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->interCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->interCellYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->interCellCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               ( RsMXBoundaryOutDB->interCellCenterRotateAngleDB[i][iRingNum][cellNum] );
					////               fout << "After RotateY" << endl;
					////               fout << "RightUpCenterRadianDB: "
					////                    << RsMXBoundaryOutDB->boundaryCellRightUpCenterRotateAngleDB[i][iRingNum][cellNum] <<endl;
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->interCellXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->interCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->interCellYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryOutCellNum += 1;
				}
			}
		}
	}
	fout << "MXBoundaryOutCellNum: " << MXBoundaryOutCellNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}


/////////////////////////////////////////////// MXBoundaryUpCellVisual ///////////////////////////////////////////
void rsMXBoundaryOutVisual::MXBoundaryUpCellVisual
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

	int MXBoundaryInterCellNum = 0;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer->SetFileName("MXBoundaryUpCell.vtp");

	ofstream fout("staticNum.txt", ios::app);

	for (itMap = RsMXBoundaryOutDB->upCellObjectHeightDB.begin(), i = 0;
		itMap != RsMXBoundaryOutDB->upCellObjectHeightDB.end();
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
					//               cout << "rsMXBoundaryOutVisual: " << "i: " << i << "  iRingNum: " << iRingNum
					//               << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum << endl;
					superEllipsoid->SetXRadius
					(RsMXBoundaryOutDB->upVerticalLengthHalfDB[i][iRingNum]);

					superEllipsoid->SetYRadius
					(RsMXBoundaryOutDB->upParallelLengthHalfDB[i][iRingNum]);
					/// Right Up;
					superEllipsoid->SetZRadius
					(RsMXBoundaryOutDB->upCellObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

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

					trans->Translate(RsMXBoundaryOutDB->upCellXDB[i][iRingNum][cellNum],
						RsMXBoundaryOutDB->upCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsMXBoundaryOutDB->upCellYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsMXBoundaryOutDB->upCellCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               ( RsMXBoundaryOutDB->upCellCenterRotateAngleDB[i][iRingNum][cellNum] );
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsMXBoundaryOutDB->upCellXDB[i][iRingNum][cellNum],
					//                 RsMXBoundaryOutDB->upCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsMXBoundaryOutDB->upCellYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
					//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

					renL->AddActor(actor);
					MXBoundaryInterCellNum += 1;
				}
			}
		}
	}

	fout << "MXBoundaryInterCellNum: " << MXBoundaryInterCellNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}