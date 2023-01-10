#include "rsSteleInnerVisual.h"
#include "globals.h"

void rsSteleInnerVisual::SteleInnerVisual
(rsSteleInnerDB* RsSteleInnerDB,
	vtkSmartPointer<vtkRenderer> renL)
{  /// declare iterator;
	map<int, vector< vector<double> > >::iterator itMap;
	vector< vector<double> >::iterator itVec2;
	vector<double>::iterator           itVec1;
	/// declare int;
	int iRingNum;
	int i;
	int sliceTempNum;


	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "SteleInnerCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("SteleInnerCell.vtp");

	ofstream fout(getFolderName() + "Stele.txt", ios::app);

	for (iRingNum = 0, itMap = RsSteleInnerDB->objectHeightDB.begin();
		itMap != RsSteleInnerDB->objectHeightDB.end();
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

				fout << RsSteleInnerDB->steleInnerObjectVerticalDB[iRingNum] << endl;
				superEllipsoid->SetXRadius
				(RsSteleInnerDB->steleInnerObjectVerticalDB[iRingNum]);

				fout << RsSteleInnerDB->circleSegmentLengthDB[iRingNum][i] << endl;
				superEllipsoid->SetYRadius
				(RsSteleInnerDB->circleSegmentLengthDB[iRingNum][i]);

				fout << RsSteleInnerDB->objectHeightDB[iRingNum][i][sliceTempNum] << endl;
				superEllipsoid->SetZRadius
				(RsSteleInnerDB->objectHeightDB[iRingNum][i][sliceTempNum]);

				superEllipsoid->SetN1(0.2);
				superEllipsoid->SetN2(0.8);

				superEllipsoidFunction->SetParametricFunction(superEllipsoid);
				superEllipsoidFunction->SetUResolution(RsSteleInnerDB->uResolution);
				superEllipsoidFunction->SetVResolution(RsSteleInnerDB->vResolution);
				superEllipsoidFunction->SetWResolution(RsSteleInnerDB->wResolution);
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
					(numSequence, 0.5);
				}
				polydata->GetPointData()->SetScalars(scalars);
				scalars->Delete();


				/// Set vtkTranform and vtkTransformPloyDataFilter;
				vtkSmartPointer<vtkTransform> trans =
					vtkSmartPointer<vtkTransform>::New();

				vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
					vtkSmartPointer<vtkTransformPolyDataFilter>::New();

				fout << RsSteleInnerDB->circleXDB[iRingNum][i] << endl;
				fout << RsSteleInnerDB->objectZPositionDB[iRingNum][i][sliceTempNum] << endl;
				fout << RsSteleInnerDB->circleYDB[iRingNum][i] << endl;
				fout << RsSteleInnerDB->circleSegmentRotateAngleDB[iRingNum][i] << endl;

				trans->Translate(RsSteleInnerDB->circleXDB[iRingNum][i],
					RsSteleInnerDB->objectZPositionDB[iRingNum][i][sliceTempNum],
					RsSteleInnerDB->circleYDB[iRingNum][i]);
				trans->RotateY((RsSteleInnerDB->circleSegmentRotateAngleDB[iRingNum][i]));
				trans->RotateX(90);

				transFilter->SetInputData(polydata);
				transFilter->SetTransform(trans);

				/// Add transFilter to vtkAppendPolyData pointer everytime;
				append->AddInputConnection(transFilter->GetOutputPort());

				/// vtkPolyDataMapper and vtkActor;
				polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
				actor->SetMapper(polyDataMapper);

				actor->GetProperty()->SetOpacity(RsSteleInnerDB->objectOpacity);

				renL->AddActor(actor);
			}
		}
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}


void rsSteleInnerVisual::SteleInnestVisual
(rsSteleInnerDB* RsSteleInnerDB,
	vtkSmartPointer<vtkRenderer> renL)
{
	vector<double>::iterator           itVec;

	int sliceTempNum;
	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "SteleInnestCell.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("SteleInnestCell.vtp");

	ofstream fout(getFolderName() + "Stele.txt", ios::app);

	for (sliceTempNum = 0, itVec = RsSteleInnerDB->steleInnestObjectHeightDB.begin();
		itVec != RsSteleInnerDB->steleInnestObjectHeightDB.end();
		sliceTempNum++, itVec++)
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
		(RsSteleInnerDB->steleInnestCellRadius);

		superEllipsoid->SetYRadius
		(RsSteleInnerDB->steleInnestCellRadius);

		superEllipsoid->SetZRadius
		(RsSteleInnerDB->steleInnestObjectHeightDB[sliceTempNum]);

		superEllipsoid->SetN1(0.2);
		superEllipsoid->SetN2(1);

		superEllipsoidFunction->SetParametricFunction(superEllipsoid);
		superEllipsoidFunction->SetUResolution(RsSteleInnerDB->uResolution);
		superEllipsoidFunction->SetVResolution(RsSteleInnerDB->vResolution);
		superEllipsoidFunction->SetWResolution(RsSteleInnerDB->wResolution);
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
			(numSequence, 0.5);
		}
		polydata->GetPointData()->SetScalars(scalars);
		scalars->Delete();

		/// Set vtkTranform and vtkTransformPloyDataFilter;
		vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		trans->Translate(0,
			RsSteleInnerDB->steleInnestObjectZPositionDB[sliceTempNum],
			0);
		trans->RotateX(90);

		transFilter->SetInputData(polydata);
		transFilter->SetTransform(trans);

		/// Add transFilter to vtkAppendPolyData pointer everytime;
		append->AddInputConnection(transFilter->GetOutputPort());

		/// vtkPolyDataMapper and vtkActor;
		polyDataMapper->SetInputConnection(transFilter->GetOutputPort());
		actor->SetMapper(polyDataMapper);

		actor->GetProperty()->SetOpacity(RsSteleInnerDB->objectOpacity);

		renL->AddActor(actor);
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}