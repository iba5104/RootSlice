#include "rsSourceDermisVisual.h"
#include "globals.h"

////////////////////////////////////// Functions ///////////////////////////////////////////

void rsSourceDermisVisual::EpidermisVisual
(rsSourceDermisDB* EpidermisDB,
	vtkSmartPointer<vtkRenderer> renL,
	int vacuolePlasmaFlag,
	vector<double> result,
	string filePrefix)
{  /// declare iterator;
	map<int, vector< vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator           itVec1;
	/// declare int;
	int iRingNum;
	int i;
	int sliceTempNum;
	int cellCtr = 0;

	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string outputFileName = EpidermisDB->outputXMLVtpFileName;
	if (vacuolePlasmaFlag == 0)
		outputFileName = "pureCell_" + outputFileName;
	if (vacuolePlasmaFlag == 1)
		outputFileName = "vacuole_" + outputFileName;
	outputFileName = filePrefix + outputFileName;
	string flName = getFolderName() + outputFileName;
	writer->SetFileName(flName.c_str());
	addToFileNamesVector(outputFileName);

	for (iRingNum = 0, itMap = EpidermisDB->objectHeightDB.begin();
		itMap != EpidermisDB->objectHeightDB.end();
		iRingNum++, itMap++)
	{
		for (i = 0, itVec2 = (*itMap).second.begin(); itVec2 != (*itMap).second.end(); i++, itVec2++)
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

				if (vacuolePlasmaFlag == 0) {
					superEllipsoid->SetXRadius(EpidermisDB->pureCellVerticalDB[iRingNum]);
					superEllipsoid->SetYRadius(EpidermisDB->pureCellParallelDB[iRingNum][i]);
					superEllipsoid->SetZRadius(EpidermisDB->pureCellHeightDB[iRingNum][i][sliceTempNum]);
				}
				else if (vacuolePlasmaFlag == 1) {
					superEllipsoid->SetXRadius(EpidermisDB->vacuoleVerticalDB[iRingNum]);
					superEllipsoid->SetYRadius(EpidermisDB->vacuoleParallelDB[iRingNum][i]);
					superEllipsoid->SetZRadius(EpidermisDB->vacuoleHeightDB[iRingNum][i][sliceTempNum]);
				}
				else {
					superEllipsoid->SetXRadius(EpidermisDB->objectVerticalDB[iRingNum]);
					superEllipsoid->SetYRadius(EpidermisDB->circleSegmentLengthDB[iRingNum][i]);
					superEllipsoid->SetZRadius(EpidermisDB->objectHeightDB[iRingNum][i][sliceTempNum]);
				}
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
					double insrtVal = (cellCtr < result.size()) ? result[cellCtr] : 0;
					scalars->InsertTuple1
						//            ( numSequence, double(sliceTempNum) / 6 );
						(numSequence, insrtVal);
				}
				polydata->GetPointData()->SetScalars(scalars);
				//scalars->Delete();


				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				trans->Translate(EpidermisDB->circleXDB[iRingNum][i],
					EpidermisDB->objectZPositionDB[iRingNum][i][sliceTempNum],
					EpidermisDB->circleYDB[iRingNum][i]);
				trans->RotateY(EpidermisDB->circleSegmentRotateAngleDB[iRingNum][i]);
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
			cellCtr++;
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}