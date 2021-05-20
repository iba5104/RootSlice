#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsPXCoreVisual.h"

// Store the objects of each ring into the different vectors;
//
void rsPXCoreVisual::PXCoreVisual
(rsPXBoundaryDB* RsPXBoundaryDB,
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

	int PXCoreNum = 0;

	ofstream fout("staticNum.txt", ios::app);

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer->SetFileName("PXCore.vtp");

	/// cout << circleSegmentLengthDB;
	for (itMap = RsPXBoundaryDB->xylemOutRingObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->xylemOutRingObjectHeightDB.end();
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

				superEllipsoid->SetXRadius
				(RsPXBoundaryDB->xylemOutRingObjectVerticalDB[i]);

				superEllipsoid->SetYRadius
				(RsPXBoundaryDB->xylemOutRingCircleSegmentLengthDB[i][cellNum]);

				superEllipsoid->SetZRadius
				(RsPXBoundaryDB->xylemOutRingObjectHeightDB[i][cellNum][sliceTempNum]);

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
						//               ( numSequence, double(sliceTempNum) / 6 );
						(numSequence, 0.0369004);
				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();

				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(RsPXBoundaryDB->xylemOutRingCircleXDB[i][cellNum],
					RsPXBoundaryDB->xylemOutRingObjectZPositionDB[i][cellNum][sliceTempNum],
					RsPXBoundaryDB->xylemOutRingCircleYDB[i][cellNum]);
				trans->RotateY(RsPXBoundaryDB->xylemOutRingCircleSegmentRotateAngleDB[i][cellNum]);
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
				//
				//            actor->RotateY
				//            ( (RsPXBoundaryDB->xylemOutRingCircleSegmentRotateAngleDB[i][cellNum]) );
				//
				//            actor->RotateX( 90 );
				//
				//            actor->SetPosition
				//            ( RsPXBoundaryDB->xylemOutRingCircleXDB[i][cellNum],
				//              RsPXBoundaryDB->xylemOutRingObjectZPositionDB[i][cellNum][sliceTempNum],
				//              RsPXBoundaryDB->xylemOutRingCircleYDB[i][cellNum] );
				//
				//            actor->GetProperty()->SetColor
				//            ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
				//              RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
				//              RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
				//            actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

				renL->AddActor(actor);

				PXCoreNum += 1;
			}
		}
	}
	fout << "PXCoreNum: " << PXCoreNum << endl;
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}

/////////////////////////////////////  PXCenterRingVisual  ////////////////////////////////////////
void rsPXCoreVisual::PXCenterRingVisual
(rsPXBoundaryDB* RsPXBoundaryDB,
	vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int sliceTempNum;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer->SetFileName("PXCenterRing.vtp");

	/// cout << circleSegmentLengthDB;
	for (itMap = RsPXBoundaryDB->xylemCenterRingObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->xylemCenterRingObjectHeightDB.end();
		itMap++, i++)
	{
		for (sliceTempNum = 0, itVec1 = (*itMap).second.begin();
			itVec1 != (*itMap).second.end();
			sliceTempNum++, itVec1++)
		{
			vtkSmartPointer<vtkCylinderSource> cylinder
				= vtkSmartPointer<vtkCylinderSource>::New();

			vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
				= vtkSmartPointer<vtkPolyDataMapper>::New();

			vtkSmartPointer<vtkActor> actor
				= vtkSmartPointer<vtkActor>::New();

			cylinder->SetCenter
			(RsPXBoundaryDB->centerX[i],
				RsPXBoundaryDB->xylemCenterRingObjectZPositionDB[i][sliceTempNum],
				RsPXBoundaryDB->centerY[i]);

			cylinder->SetRadius(RsPXBoundaryDB->eachRingRadius[i]);
			cylinder->SetHeight(RsPXBoundaryDB->xylemCenterRingObjectHeightDB[i][sliceTempNum]);
			cylinder->SetResolution(20);
			cylinder->SetCapping(0);

			/// You need to update() if you want to output the data of object;
			cylinder->Update();

			/// Set Scalars;
			// Extract the polydata
			vtkSmartPointer<vtkPolyData> polydata =
				vtkSmartPointer<vtkPolyData>::New();
			polydata = cylinder->GetOutput();

			int pointNum;
			pointNum = polydata->GetNumberOfPoints();

			vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
			scalars->SetName("Color");
			int numSequence;

			/// Add scalar to point;
			for (numSequence = 0; numSequence < pointNum; numSequence++)
			{
				scalars->InsertTuple1
				(numSequence, 0.252768);
				//            ( numSequence, double(sliceTempNum) / 4 );
			}
			polydata->GetPointData()->SetScalars(scalars);

			/// Add polydata to vtkAppendPolyData pointer everytime;
			append->AddInputData(polydata);

			/// vtkPolyDataMapper and vtkActor;
			polyDataMapper->SetInputData(polydata);
			polyDataMapper->SetInputData(polydata);
			actor->SetMapper(polyDataMapper);

			//         polyDataMapper->SetInputConnection
			//         ( cylinder->GetOutputPort() );
			//
			//         actor->SetMapper( polyDataMapper );
			//
			//         actor->GetProperty()->SetColor
			//         ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
			//           RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
			//           RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
			//         actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

			renL->AddActor(actor);
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}

//////////////////////////////////// PXSmallVisual ///////////////////////////////////////////////
void rsPXCoreVisual::PXSmallVisual
(rsPXBoundaryDB* RsPXBoundaryDB,
	vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVec1;
	/// declare int;
	int i;
	int sliceTempNum;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer->SetFileName("PXSmall.vtp");


	for (itMap = RsPXBoundaryDB->xylemCenterRingObjectHeightDB.begin(), i = 0;
		itMap != RsPXBoundaryDB->xylemCenterRingObjectHeightDB.end();
		itMap++, i++)
	{
		for (sliceTempNum = 0, itVec1 = (*itMap).second.begin();
			itVec1 != (*itMap).second.end();
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
			(RsPXBoundaryDB->pxSmallVerticalRadiusDB[i]);

			superEllipsoid->SetYRadius
			(RsPXBoundaryDB->pxSmallParallelRadiusDB[i]);

			superEllipsoid->SetZRadius
			(RsPXBoundaryDB->pxSmallCenterRingObjectHeightDB[i][sliceTempNum]);


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

			int pointNum, cellNum;
			pointNum = polydata->GetNumberOfPoints();
			cellNum = polydata->GetNumberOfCells();

			vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
			scalars->SetName("Color");
			int numSequence;

			/// Add scalar to point;
			for (numSequence = 0; numSequence < pointNum; numSequence++)
			{
				scalars->InsertTuple1
					//            ( numSequence, double(sliceTempNum) / 5 );
					(numSequence, 0.7);

			}
			polydata->GetPointData()->SetScalars(scalars);


			/// Set vtkTranform and vtkTransformPloyDataFilter;
			vtkSmartPointer<vtkTransform> trans =
				vtkSmartPointer<vtkTransform>::New();

			vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
				vtkSmartPointer<vtkTransformPolyDataFilter>::New();

			trans->Translate(RsPXBoundaryDB->centerXPXSmall[i],
				RsPXBoundaryDB->xylemCenterRingObjectZPositionDB[i][sliceTempNum],
				RsPXBoundaryDB->centerYPXSmall[i]);
			trans->RotateY(RsPXBoundaryDB->centerRingRotateAngle[i]);
			trans->RotateX(90);

			transFilter->SetInputData(polydata);
			transFilter->SetTransform(trans);

			/// Add transFilter to vtkAppendPolyData pointer everytime;
			append->AddInputConnection(transFilter->GetOutputPort());

			/// vtkPolyDataMapper and vtkActor;
			polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
			actor->SetMapper(polyDataMapper);


			//         polyDataMapper->SetInputConnection
			//         ( superEllipsoidFunction->GetOutputPort() );
			//
			//         actor->SetMapper( polyDataMapper );
			//
			//         actor->RotateY
			//         ( (RsPXBoundaryDB->centerRingRotateAngle[i]) );
			//
			//         actor->RotateX( 90 );
			//
			//         actor->SetPosition
			//         ( RsPXBoundaryDB-> centerXPXSmall[i],
			//           RsPXBoundaryDB-> xylemCenterRingObjectZPositionDB[i][sliceTempNum],
			//           RsPXBoundaryDB-> centerYPXSmall[i] );
			//
			//         actor->GetProperty()->SetColor
			//         ( RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][0],
			//           RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][1],
			//           RsPXBoundaryDB->mapRGB[sliceTempNum*RsPXBoundaryDB->rgbTime + RsPXBoundaryDB->rgbStart][2] );
			//         actor->GetProperty()->SetOpacity( RsPXBoundaryDB -> objectOpacity );

			renL->AddActor(actor);
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}