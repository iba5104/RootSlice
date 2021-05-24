#include "rsSourceEpidermisVisual.h"


////////////////////////////////////// Functions ///////////////////////////////////////////

void rsSourceEpidermisVisual::EpidermisVisual
(rsSourceEpidermisDB* EpidermisDB,
	vtkSmartPointer<vtkRenderer> renL)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMap;
	vector<double>::iterator itVector;
	/// declare int;
	int i;
	int sliceTempNum;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer->SetFileName(EpidermisDB->outputXMLVtpFileName);

	for (i = 0, itMap = EpidermisDB->objectHeightDB.begin();
		itMap != EpidermisDB->objectHeightDB.end();
		i++, itMap++)
	{
		for (sliceTempNum = 0, itVector = (*itMap).second.begin();
			itVector != (*itMap).second.end();
			sliceTempNum++, itVector++)
		{
			vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
				= vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

			vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
				= vtkSmartPointer<vtkParametricFunctionSource>::New();

			vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
				= vtkSmartPointer<vtkPolyDataMapper>::New();

			vtkSmartPointer<vtkActor> actor
				= vtkSmartPointer<vtkActor>::New();

			superEllipsoid->SetXRadius(EpidermisDB->objectVerticalDB);
			superEllipsoid->SetYRadius(EpidermisDB->circleSegmentLengthDB[i]);
			superEllipsoid->SetZRadius(EpidermisDB->objectHeightDB[i][sliceTempNum]);
			superEllipsoid->SetN1(0.2);
			superEllipsoid->SetN2(0.8);

			superEllipsoidFunction->SetParametricFunction(superEllipsoid);
			superEllipsoidFunction->SetUResolution(EpidermisDB->uResolution);
			superEllipsoidFunction->SetVResolution(EpidermisDB->vResolution);
			superEllipsoidFunction->SetWResolution(EpidermisDB->wResolution);
			superEllipsoidFunction->Update();

			/// Set Scalars;
			// Extract the polydata
			vtkSmartPointer<vtkPolyData> polydata =
				vtkSmartPointer<vtkPolyData>::New();
			polydata = superEllipsoidFunction->GetOutput();

			int pointNum;
			pointNum = polydata->GetNumberOfPoints();

			//         vtkFloatArray *scalars = vtkFloatArray::New();
			vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
			scalars->SetName("Color");
			int numSequence;

			/// Add scalar to point;
			for (numSequence = 0; numSequence < pointNum; numSequence++)
			{
				scalars->InsertTuple1
					//            ( numSequence, double(sliceTempNum) / 6 );
					(numSequence, 0.9);
			}
			polydata->GetPointData()->SetScalars(scalars);
			//scalars->Delete();


			/// Set vtkTranform and vtkTransformPloyDataFilter;
			vtkSmartPointer<vtkTransform> trans =
				vtkSmartPointer<vtkTransform>::New();

			vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
				vtkSmartPointer<vtkTransformPolyDataFilter>::New();

			trans->Translate(EpidermisDB->circleXDB[i],
				EpidermisDB->objectZPositionDB[i][sliceTempNum],
				EpidermisDB->circleYDB[i]);
			trans->RotateY(EpidermisDB->circleSegmentRotateAngleDB[i]);
			trans->RotateX(90);

			transFilter->SetInputData(polydata);
			transFilter->SetTransform(trans);

			/// Add transFilter to vtkAppendPolyData pointer everytime;
			append->AddInputConnection(transFilter->GetOutputPort());

			/// vtkPolyDataMapper and vtkActor;
			polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
			actor->SetMapper(polyDataMapper);

			//         actor->RotateY( (EpidermisDB->circleSegmentRotateAngleDB[i]) );
			//         actor->RotateX( 90 );
			//
			//         actor->SetPosition( EpidermisDB->circleXDB[i],
			//                             EpidermisDB->objectZPositionDB[i][sliceTempNum],
			//                             EpidermisDB->circleYDB[i] );
			//
			//
			//         actor->GetProperty()->SetColor
			//         ( EpidermisDB->mapRGB[sliceTempNum*EpidermisDB->rgbTime + EpidermisDB->rgbStart][0],
			//           EpidermisDB->mapRGB[sliceTempNum*EpidermisDB->rgbTime + EpidermisDB->rgbStart][1],
			//           EpidermisDB->mapRGB[sliceTempNum*EpidermisDB->rgbTime + EpidermisDB->rgbStart][2] );
			actor->GetProperty()->SetOpacity(EpidermisDB->objectOpacity);

			renL->AddActor(actor);
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}