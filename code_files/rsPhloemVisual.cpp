#include "rsPhloemVisual.h"
#include "globals.h"

/////////////////////////////////////////////// UpAppendCellVisual ///////////////////////////////////////////
void rsPhloemVisual::UpAppendCellVisual
(rsPhloemDB* RsPhloemDB,
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

	int PhloemAppendCellNum = 0;

	//ofstream fout("staticNum.txt",ios::app);
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpAppendCellVisual" << endl;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "UpPhloemAppendCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("UpPhloemAppendCell.vtp");

	/// UpAppendCellVisual - Start;
	fout << "UpAppendCellVisual - Start" << endl;
	for (itMap = RsPhloemDB->upAppendStartCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->upAppendStartCellObjectHeightDB.end();
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

					fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
						<< "  sliceTempNum: " << sliceTempNum << endl;

					superEllipsoid->SetXRadius
					(RsPhloemDB->upAppendVerticalLengthHalfDB[i]);
					fout << "Vertical: " << RsPhloemDB->upAppendVerticalLengthHalfDB[i];

					superEllipsoid->SetYRadius
					(RsPhloemDB->upAppendParallelStartLengthHalfDB[i][iRingNum]);
					fout << "  Parallel: " << RsPhloemDB->upAppendParallelStartLengthHalfDB[i][iRingNum];

					superEllipsoid->SetZRadius
					(RsPhloemDB->upAppendStartCellObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);
					fout << "  Height: " << RsPhloemDB->upAppendStartCellObjectHeightDB[i][iRingNum][cellNum][sliceTempNum];

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);


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
							(numSequence, 0.3);
					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPhloemDB->upAppendStartCellXDB[i][iRingNum][cellNum],
						RsPhloemDB->upAppendStartCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPhloemDB->upAppendStartCellYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPhloemDB->upAppendParallelStartCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               ( RsPhloemDB->upAppendParallelStartCenterRotateAngleDB[i][iRingNum][cellNum] );
					//               fout << "  RotateY: " << RsPhloemDB->upAppendParallelStartCenterRotateAngleDB[i][iRingNum][cellNum];
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPhloemDB->upAppendStartCellXDB[i][iRingNum][cellNum],
					//                 RsPhloemDB->upAppendStartCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPhloemDB->upAppendStartCellYDB[i][iRingNum][cellNum] );
					//               fout << "  X: " << RsPhloemDB->upAppendStartCellXDB[i][iRingNum][cellNum];
					//               fout << "  Y: " << RsPhloemDB->upAppendStartCellYDB[i][iRingNum][cellNum];
					//               fout << "  Z: " << RsPhloemDB->upAppendStartCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum] << endl;
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
					//                 RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
					//                 RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

					renL->AddActor(actor);
					PhloemAppendCellNum += 1;
				}
			}
		}
	}

	/// UpAppendCellVisual - End;
	fout << "UpAppendCellVisual - End" << endl;
	for (itMap = RsPhloemDB->upAppendEndCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->upAppendEndCellObjectHeightDB.end();
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
					(RsPhloemDB->upAppendVerticalLengthHalfDB[i]);

					superEllipsoid->SetYRadius
					(RsPhloemDB->upAppendParallelEndLengthHalfDB[i][iRingNum]);

					superEllipsoid->SetZRadius
					(RsPhloemDB->upAppendEndCellObjectHeightDB[i][iRingNum][cellNum][sliceTempNum]);

					superEllipsoid->SetN1(0.2);
					superEllipsoid->SetN2(0.8);

					superEllipsoidFunction->SetParametricFunction(superEllipsoid);
					superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
					superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
					superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);

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
							(numSequence, 0.3);
					}
					polydata->GetPointData()->SetScalars(scalars);
					scalars->Delete();

					/// Set vtkTranform and vtkTransformPloyDataFilter;
					vtkSmartPointer<vtkTransform> trans =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();

					trans->Translate(RsPhloemDB->upAppendEndCellXDB[i][iRingNum][cellNum],
						RsPhloemDB->upAppendEndCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
						RsPhloemDB->upAppendEndCellYDB[i][iRingNum][cellNum]);
					trans->RotateY(RsPhloemDB->upAppendParallelEndCenterRotateAngleDB[i][iRingNum][cellNum]);
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
					//               ( RsPhloemDB->upAppendParallelEndCenterRotateAngleDB[i][iRingNum][cellNum] );
					//
					//               fout << "i: " << i << "  iRingNum: " << iRingNum << "  cellNum: " << cellNum
					//                    << "  sliceTempNum: " << sliceTempNum << endl;
					//
					//               actor->RotateX( 90 );
					//
					//               actor->SetPosition
					//               ( RsPhloemDB->upAppendEndCellXDB[i][iRingNum][cellNum],
					//                 RsPhloemDB->upAppendEndCellObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
					//                 RsPhloemDB->upAppendEndCellYDB[i][iRingNum][cellNum] );
					//
					//               actor->GetProperty()->SetColor
					//               ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
					//                 RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
					//                 RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
					//               actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

					renL->AddActor(actor);
					PhloemAppendCellNum += 1;
				}
			}
		}
	}
	fout << "PhloemAppendCellNum: " << PhloemAppendCellNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}

///////////////////////////////////////  Phloem  //////////////////////////////////////////////////
void rsPhloemVisual::UpPhloemCellVisual
(rsPhloemDB* RsPhloemDB,
	vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int cellNum;
	int sliceTempNum;

	int PhloemCellNum = 0;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "UpPhloemCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("UpPhloemCell.vtp");

	//ofstream fout("staticNum.txt",ios::app);
	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "UpPhloemCellVisual" << endl;
	/// Phloem - First;
	fout << "First" << endl;
	for (itMap = RsPhloemDB->upFirstPhloemCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->upFirstPhloemCellObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec2 = (*itMap).second.begin(), cellNum = 0;
			itVec2 != (*itMap).second.end();
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

				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum << endl;

				superEllipsoid->SetXRadius
				(RsPhloemDB->phloemVerticalLengthHalfDB[i]);
				fout << "Vertical: " << RsPhloemDB->phloemVerticalLengthHalfDB[i];

				superEllipsoid->SetYRadius
				(RsPhloemDB->upFirstPhloemParallelLengthSegmentHalfDB[i][cellNum]);
				fout << "  Parallel: " << RsPhloemDB->upFirstPhloemParallelLengthSegmentHalfDB[i][cellNum];

				superEllipsoid->SetZRadius
				(RsPhloemDB->upFirstPhloemCellObjectHeightDB[i][cellNum][sliceTempNum]);
				fout << "  Height: " << RsPhloemDB->upFirstPhloemCellObjectHeightDB[i][cellNum][sliceTempNum];

				superEllipsoid->SetN1(0.2);
				superEllipsoid->SetN2(0.8);

				superEllipsoidFunction->SetParametricFunction(superEllipsoid);
				superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
				superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
				superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);

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
						//               ( numSequence, double(sliceTempNum) / 4 );
						(numSequence, 1);
				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();

				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(RsPhloemDB->upFirstPhloemParallelCellXDB[i][cellNum],
					RsPhloemDB->upFirstPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum],
					RsPhloemDB->upFirstPhloemParallelCellYDB[i][cellNum]);
				trans->RotateY(RsPhloemDB->upFirstPhloemParallelCenterRotateAngleDB[i][cellNum]);
				trans->RotateX(90);

				transFilter->SetInputData(polydata);
				transFilter->SetTransform(trans);

				/// Add transFilter to vtkAppendPolyData pointer everytime;
				append->AddInputConnection(transFilter->GetOutputPort());

				/// vtkPolyDataMapper and vtkActor;
				polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
				actor->SetMapper(polyDataMapper);

				//            polyDataMapper->SetInputConnection
				//            ( superEllipsoidFunction->GetOutputPort() );
				//
				//            actor->SetMapper( polyDataMapper );
				//
				//            actor->RotateY
				//            ( RsPhloemDB->upFirstPhloemParallelCenterRotateAngleDB[i][cellNum] );
				//            fout << "  RotateY: " << RsPhloemDB->upFirstPhloemParallelCenterRotateAngleDB[i][cellNum];
				//
				//            actor->RotateX( 90 );
				//
				//            actor->SetPosition
				//            ( RsPhloemDB->upFirstPhloemParallelCellXDB[i][cellNum],
				//              RsPhloemDB->upFirstPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum],
				//              RsPhloemDB->upFirstPhloemParallelCellYDB[i][cellNum] );
				//            fout << "  X: " << RsPhloemDB->upFirstPhloemParallelCellXDB[i][cellNum];
				//            fout << "  Y: " << RsPhloemDB->upFirstPhloemParallelCellYDB[i][cellNum];
				//            fout << "  Z: " << RsPhloemDB->upFirstPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum] << endl;
				//
				//            actor->GetProperty()->SetColor
				//            ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
				//            actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

				renL->AddActor(actor);
				PhloemCellNum += 1;
			}
		}
	}
	/// Phloem - Second;
	fout << "Second" << endl;
	for (itMap = RsPhloemDB->upSecondPhloemCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->upSecondPhloemCellObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec2 = (*itMap).second.begin(), cellNum = 0;
			itVec2 != (*itMap).second.end();
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

				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum << endl;

				superEllipsoid->SetXRadius
				(RsPhloemDB->phloemVerticalLengthHalfDB[i]);
				fout << "Vertical: " << RsPhloemDB->phloemVerticalLengthHalfDB[i];

				superEllipsoid->SetYRadius
				(RsPhloemDB->upSecondPhloemParallelLengthSegmentHalfDB[i][cellNum]);
				fout << "  Parallel: " << RsPhloemDB->upSecondPhloemParallelLengthSegmentHalfDB[i][cellNum];

				superEllipsoid->SetZRadius
				(RsPhloemDB->upSecondPhloemCellObjectHeightDB[i][cellNum][sliceTempNum]);
				fout << "  Height: " << RsPhloemDB->upSecondPhloemCellObjectHeightDB[i][cellNum][sliceTempNum];

				superEllipsoid->SetN1(0.2);
				superEllipsoid->SetN2(0.8);

				superEllipsoidFunction->SetParametricFunction(superEllipsoid);
				superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
				superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
				superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);

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
						//               ( numSequence, double(sliceTempNum) / 4 );
						(numSequence, 1);

				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();

				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(RsPhloemDB->upSecondPhloemParallelCellXDB[i][cellNum],
					RsPhloemDB->upSecondPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum],
					RsPhloemDB->upSecondPhloemParallelCellYDB[i][cellNum]);
				trans->RotateY(RsPhloemDB->upSecondPhloemParallelCenterRotateAngleDB[i][cellNum]);
				trans->RotateX(90);

				transFilter->SetInputData(polydata);
				transFilter->SetTransform(trans);

				/// Add transFilter to vtkAppendPolyData pointer everytime;
				append->AddInputConnection(transFilter->GetOutputPort());

				/// vtkPolyDataMapper and vtkActor;
				polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
				actor->SetMapper(polyDataMapper);

				//            polyDataMapper->SetInputConnection
				//            ( superEllipsoidFunction->GetOutputPort() );
				//
				//            actor->SetMapper( polyDataMapper );
				//
				//            actor->RotateY
				//            ( RsPhloemDB->upSecondPhloemParallelCenterRotateAngleDB[i][cellNum] );
				//            fout << "  RotateY: " << RsPhloemDB->upSecondPhloemParallelCenterRotateAngleDB[i][cellNum];
				//
				//            actor->RotateX( 90 );
				//
				//            actor->SetPosition
				//            ( RsPhloemDB->upSecondPhloemParallelCellXDB[i][cellNum],
				//              RsPhloemDB->upSecondPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum],
				//              RsPhloemDB->upSecondPhloemParallelCellYDB[i][cellNum] );
				//            fout << "  X: " << RsPhloemDB->upSecondPhloemParallelCellXDB[i][cellNum];
				//            fout << "  Y: " << RsPhloemDB->upSecondPhloemParallelCellYDB[i][cellNum];
				//            fout << "  Z: " << RsPhloemDB->upSecondPhloemCellObjectZPositionDB[i][cellNum][sliceTempNum] << endl;
				//
				//            actor->GetProperty()->SetColor
				//            ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
				//            actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

				renL->AddActor(actor);
				PhloemCellNum += 1;
			}
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}

////////////////////////////////////// Down Cell /////////////////////////////////////////////////

void rsPhloemVisual::DownCellVisual
(rsPhloemDB* RsPhloemDB,
	vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
	map<int, vector <vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int cellNum;
	int sliceTempNum;

	int PhloemCellNum = 0;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "PhloemDownCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("PhloemDownCell.vtp");


	ofstream fout(getFolderName() + "phloemUpAppendCell.txt", ios::app);
	fout << "DownCellVisual" << endl;

	/// downFirst;
	fout << "First" << endl;
	for (itMap = RsPhloemDB->downFirstCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->downFirstCellObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec2 = (*itMap).second.begin(), cellNum = 0;
			itVec2 != (*itMap).second.end();
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

				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum << endl;

				superEllipsoid->SetXRadius
				(RsPhloemDB->downFirstVerticalLengthHalfDB[i]);
				fout << "Vertical: " << RsPhloemDB->downFirstVerticalLengthHalfDB[i];

				superEllipsoid->SetYRadius
				(RsPhloemDB->downFirstParallelLengthHalfDB[i][cellNum]);
				fout << "  Parallel: " << RsPhloemDB->downFirstParallelLengthHalfDB[i][cellNum];

				superEllipsoid->SetZRadius
				(RsPhloemDB->downFirstCellObjectHeightDB[i][cellNum][sliceTempNum]);
				fout << "  Height: " << RsPhloemDB->downFirstCellObjectHeightDB[i][cellNum][sliceTempNum];

				superEllipsoid->SetN1(0.2);
				superEllipsoid->SetN2(0.8);

				superEllipsoidFunction->SetParametricFunction(superEllipsoid);
				superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
				superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
				superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);

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
						//               ( numSequence, double(sliceTempNum) / 6 );
						(numSequence, 0.3);

				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();

				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(RsPhloemDB->downFirstCellXDB[i][cellNum],
					RsPhloemDB->downFirstCellObjectZPositionDB[i][cellNum][sliceTempNum],
					RsPhloemDB->downFirstCellYDB[i][cellNum]);
				trans->RotateY(RsPhloemDB->downFirstParallelCenterRotateAngleDB[i][cellNum]);
				trans->RotateX(90);

				transFilter->SetInputData(polydata);
				transFilter->SetTransform(trans);

				/// Add transFilter to vtkAppendPolyData pointer everytime;
				append->AddInputConnection(transFilter->GetOutputPort());

				/// vtkPolyDataMapper and vtkActor;
				polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
				actor->SetMapper(polyDataMapper);

				//            polyDataMapper->SetInputConnection
				//            ( superEllipsoidFunction->GetOutputPort() );
				//
				//            actor->SetMapper( polyDataMapper );
				//
				//            actor->RotateY
				//            ( RsPhloemDB->downFirstParallelCenterRotateAngleDB[i][cellNum] );
				//            fout << "  RotateY: " << RsPhloemDB->downFirstParallelCenterRotateAngleDB[i][cellNum];
				//
				//            actor->RotateX( 90 );
				//
				//            actor->SetPosition
				//            ( RsPhloemDB->downFirstCellXDB[i][cellNum],
				//              RsPhloemDB->downFirstCellObjectZPositionDB[i][cellNum][sliceTempNum],
				//              RsPhloemDB->downFirstCellYDB[i][cellNum] );
				//            fout << "  X: " << RsPhloemDB->downFirstCellXDB[i][cellNum];
				//            fout << "  Y: " << RsPhloemDB->downFirstCellYDB[i][cellNum];
				//            fout << "  Z: " << RsPhloemDB->downFirstCellObjectZPositionDB[i][cellNum][sliceTempNum] << endl;
				//
				//            actor->GetProperty()->SetColor
				//            ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
				//            actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

				renL->AddActor(actor);
				PhloemCellNum += 1;
			}
		}
	}
	/// downSecond;
	fout << "Second" << endl;
	for (itMap = RsPhloemDB->downSecondCellObjectHeightDB.begin(), i = 0;
		itMap != RsPhloemDB->downSecondCellObjectHeightDB.end();
		itMap++, i++)
	{
		for (itVec2 = (*itMap).second.begin(), cellNum = 0;
			itVec2 != (*itMap).second.end();
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

				fout << "i: " << i << "  cellNum: " << cellNum << "  sliceTempNum: " << sliceTempNum << endl;

				superEllipsoid->SetXRadius
				(RsPhloemDB->downSecondVerticalLengthHalfDB[i]);
				fout << "Vertical: " << RsPhloemDB->downSecondVerticalLengthHalfDB[i];

				superEllipsoid->SetYRadius
				(RsPhloemDB->downSecondParallelLengthHalfDB[i][cellNum]);
				fout << "  Parallel: " << RsPhloemDB->downSecondParallelLengthHalfDB[i][cellNum];

				superEllipsoid->SetZRadius
				(RsPhloemDB->downSecondCellObjectHeightDB[i][cellNum][sliceTempNum]);
				fout << "  Height: " << RsPhloemDB->downSecondCellObjectHeightDB[i][cellNum][sliceTempNum];

				superEllipsoid->SetN1(0.2);
				superEllipsoid->SetN2(0.8);

				superEllipsoidFunction->SetParametricFunction(superEllipsoid);
				superEllipsoidFunction->SetUResolution(RsPhloemDB->uResolution);
				superEllipsoidFunction->SetVResolution(RsPhloemDB->vResolution);
				superEllipsoidFunction->SetWResolution(RsPhloemDB->wResolution);

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
						//               ( numSequence, double(sliceTempNum) / 6 );
						(numSequence, 0.3);
				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();

				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(RsPhloemDB->downSecondCellXDB[i][cellNum],
					RsPhloemDB->downSecondCellObjectZPositionDB[i][cellNum][sliceTempNum],
					RsPhloemDB->downSecondCellYDB[i][cellNum]);
				trans->RotateY(RsPhloemDB->downSecondParallelCenterRotateAngleDB[i][cellNum]);
				trans->RotateX(90);

				transFilter->SetInputData(polydata);
				transFilter->SetTransform(trans);

				/// Add transFilter to vtkAppendPolyData pointer everytime;
				append->AddInputConnection(transFilter->GetOutputPort());

				/// vtkPolyDataMapper and vtkActor;
				polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
				actor->SetMapper(polyDataMapper);

				//            polyDataMapper->SetInputConnection
				//            ( superEllipsoidFunction->GetOutputPort() );
				//
				//            actor->SetMapper( polyDataMapper );
				//
				//            actor->RotateY
				//            ( RsPhloemDB->downSecondParallelCenterRotateAngleDB[i][cellNum] );
				//            fout << "  RotateY: " << RsPhloemDB->downSecondParallelCenterRotateAngleDB[i][cellNum];
				//
				//            actor->RotateX( 90 );
				//
				//            actor->SetPosition
				//            ( RsPhloemDB->downSecondCellXDB[i][cellNum],
				//              RsPhloemDB->downSecondCellObjectZPositionDB[i][cellNum][sliceTempNum],
				//              RsPhloemDB->downSecondCellYDB[i][cellNum] );
				//            fout << "  X: " << RsPhloemDB->downSecondCellXDB[i][cellNum];
				//            fout << "  Y: " << RsPhloemDB->downSecondCellYDB[i][cellNum];
				//            fout << "  Z: " << RsPhloemDB->downSecondCellObjectZPositionDB[i][cellNum][sliceTempNum] << endl;
				//
				//            actor->GetProperty()->SetColor
				//            ( RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][0],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][1],
				//              RsPhloemDB->mapRGB[sliceTempNum * (RsPhloemDB->rgbTime) + RsPhloemDB->rgbStart][2] );
				//            actor->GetProperty()->SetOpacity( RsPhloemDB -> objectOpacity );

				renL->AddActor(actor);
				PhloemCellNum += 1;
			}
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}