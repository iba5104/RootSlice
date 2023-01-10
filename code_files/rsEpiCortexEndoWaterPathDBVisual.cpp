#include "globals.h"
#include "rsEpiCortexEndoWaterPathDBVisual.h"

void rsEpiCortexEndoWaterPathDBVisual::ApoplastTriangleStripXMLVtp(
	rsEpiCortexEndoWaterPathDB* RsEpiCortexEndoWaterPathDB,
	globals surfaceFlux)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMapX;
	map<int, vector<double> >::iterator itMapY;
	map<int, vector<double> >::iterator itMapZ;
	vector<double>::iterator itVecX;
	vector<double>::iterator itVecY;
	vector<double>::iterator itVecZ;
	int i;


	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "ApoplastTriangleStripXML.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("ApoplastTriangleStripXML.vtp");

	/// cout << circleSegmentLengthDB;
	for (itMapX = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastTriangleStripXDB.begin(),
		itMapY = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastTriangleStripYDB.begin(),
		itMapZ = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastTriangleStripZDB.begin();
		itMapX != RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastTriangleStripXDB.end();
		itMapX++, itMapY++, itMapZ++)
	{  /// triangleStrip;
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds((itMapX->second).size());

		vtkSmartPointer<vtkCellArray> cells =
			vtkSmartPointer<vtkCellArray>::New();

		for (itVecX = (*itMapX).second.begin(),
			itVecY = (*itMapY).second.begin(),
			itVecZ = (*itMapZ).second.begin(), i = 0;
			itVecX != (*itMapX).second.end();
			itVecX++, itVecY++, itVecZ++, i++)
		{
			points->InsertNextPoint(*itVecX, *itVecY, *itVecZ);

			triangleStrip->GetPointIds()->SetId(i, i);
		}

		cells->InsertNextCell(triangleStrip);

		// Extract the polydata
		vtkSmartPointer<vtkPolyData> polydata =
			vtkSmartPointer<vtkPolyData>::New();
		polydata->SetPoints(points);
		polydata->SetStrips(cells);
		/// Set Scalars;

		int pointNum;
		pointNum = polydata->GetNumberOfPoints();

		vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
		scalars->SetName("Color");
		int numSequence;

		/// Add scalar to point;
		for (numSequence = 0; numSequence < pointNum; numSequence++)
		{
			scalars->InsertTuple1
			(numSequence, 0.5);
		}
		polydata->GetPointData()->SetScalars(scalars);

		/// Set vtkTranform and vtkTransformPloyDataFilter;
		vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		//trans->RotateY( RsPXBoundaryDB->centerRingRotateAngle[i] );
		trans->RotateX(90);

		transFilter->SetInputData(polydata);
		transFilter->SetTransform(trans);



		/// Add transFilter to vtkAppendPolyData pointer everytime;
		append->AddInputConnection(transFilter->GetOutputPort());

		//      /// Add polydata to vtkAppendPolyData pointer everytime;
		//      append->AddInput( polydata );
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}


void rsEpiCortexEndoWaterPathDBVisual::SymplastTriangleStripXMLVtp(
	rsEpiCortexEndoWaterPathDB* RsEpiCortexEndoWaterPathDB,
	globals surfaceFlux)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMapX;
	map<int, vector<double> >::iterator itMapY;
	map<int, vector<double> >::iterator itMapZ;
	vector<double>::iterator itVecX;
	vector<double>::iterator itVecY;
	vector<double>::iterator itVecZ;
	int i;


	/// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + "SymplastTriangleStripXML.vtp";
	writer->SetFileName(flName.c_str());
	addToFileNamesVector("SymplastTriangleStripXML.vtp");


	/// cout << circleSegmentLengthDB;
	for (itMapX = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastTriangleStripXDB.begin(),
		itMapY = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastTriangleStripYDB.begin(),
		itMapZ = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastTriangleStripZDB.begin();
		itMapX != RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastTriangleStripXDB.end();
		itMapX++, itMapY++, itMapZ++)
	{  /// triangleStrip;
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds((itMapX->second).size());

		vtkSmartPointer<vtkCellArray> cells =
			vtkSmartPointer<vtkCellArray>::New();

		for (itVecX = (*itMapX).second.begin(),
			itVecY = (*itMapY).second.begin(),
			itVecZ = (*itMapZ).second.begin(), i = 0;
			itVecX != (*itMapX).second.end();
			itVecX++, itVecY++, itVecZ++, i++)
		{
			points->InsertNextPoint(*itVecX, *itVecY, *itVecZ);

			triangleStrip->GetPointIds()->SetId(i, i);
		}

		cells->InsertNextCell(triangleStrip);

		// Extract the polydata
		vtkSmartPointer<vtkPolyData> polydata =
			vtkSmartPointer<vtkPolyData>::New();
		polydata->SetPoints(points);
		polydata->SetStrips(cells);
		/// Set Scalars;

		int pointNum;
		pointNum = polydata->GetNumberOfPoints();

		vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
		scalars->SetName("Color");
		int numSequence;

		fluxEqns* FluxEqns = new fluxEqns;
//		FluxEqns->flowRate(
//			surfaceFlux.hydraulicConductance,
//			surfaceFlux.reflectionCoeffecient,
//			surfaceFlux.waterPressureDiff,
//			surfaceFlux.osmoticPressureDiff
//		);

		/// Add scalar to point;
		for (numSequence = 0; numSequence < pointNum; numSequence++)
		{
			double waterFluxSurface = FluxEqns->waterFlux(
				surfaceFlux.radialConductivity,
				surfaceFlux.pressurePotentialSurface * (1.0 - ((double)numSequence/ (double)pointNum)),
				surfaceFlux.pressurePotentialXylem,
				surfaceFlux.effectiveReflectionCoefficient,
				surfaceFlux.osmoticPotentialSurface,
				surfaceFlux.osmoticPotentialXylem
			);
			scalars->InsertTuple1
			(numSequence, waterFluxSurface);
		}
		polydata->GetPointData()->SetScalars(scalars);

		/// Set vtkTranform and vtkTransformPloyDataFilter;
		vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		trans->RotateX(90);

		transFilter->SetInputData(polydata);
		transFilter->SetTransform(trans);

		/// Add transFilter to vtkAppendPolyData pointer everytime;
		append->AddInputConnection(transFilter->GetOutputPort());

	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}

void rsEpiCortexEndoWaterPathDBVisual::ApoplastTubeXMLVtp(rsEpiCortexEndoWaterPathDB* RsEpiCortexEndoWaterPathDB)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMapX;
	map<int, vector<double> >::iterator itMapY;
	map<int, vector<double> >::iterator itMapZ;
	vector<double>::iterator itVecX;
	vector<double>::iterator itVecY;
	vector<double>::iterator itVecZ;
	int i;
	int sizeVector;
	int epiPosition;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "ApoplastTubeXMLVtp" << endl;

	   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + RsEpiCortexEndoWaterPathDB->ApoplastXMLVtpFileName;
	writer->SetFileName(flName.c_str());
	addToFileNamesVector(RsEpiCortexEndoWaterPathDB->ApoplastXMLVtpFileName);


	/// cout << circleSegmentLengthDB;
	for (itMapX = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastXDB.begin(),
		itMapY = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastYDB.begin(),
		itMapZ = RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastZDB.begin(), epiPosition = 0;
		itMapX != RsEpiCortexEndoWaterPathDB->epiCortexEndoApoplastXDB.end();
		itMapX++, itMapY++, itMapZ++, epiPosition++)
	{
		sizeVector = (itMapX->second).size();
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		vtkSmartPointer<vtkCellArray> lines =
			vtkSmartPointer<vtkCellArray>::New();
		lines->InsertNextCell(sizeVector);

		for (itVecX = (*itMapX).second.begin(),
			itVecY = (*itMapY).second.begin(),
			itVecZ = (*itMapZ).second.begin(), i = 0;
			itVecX != (*itMapX).second.end();
			itVecX++, itVecY++, itVecZ++, i++)
		{
			points->InsertNextPoint(*itVecX, *itVecY, *itVecZ);
			lines->InsertCellPoint(i);
			//         fout << "epiPosition: " << epiPosition << " ringNum: " << i
			//              << "  itVecX: " << *itVecX
			//              << "  itVecY: " << *itVecY
			//              << "  itVecZ: " << *itVecZ << endl;
		}

		// Extract the polydata
		vtkSmartPointer<vtkPolyData> polydata =
			vtkSmartPointer<vtkPolyData>::New();
		polydata->SetPoints(points);
		polydata->SetLines(lines);
		/// Set Scalars;


  //      // Set tube radius
  //      vtkSmartPointer<vtkDoubleArray> tubeRadius =
  //         vtkSmartPointer<vtkDoubleArray>::New();
  //      tubeRadius->SetName("TubeRadius");
  //      tubeRadius->SetNumberOfTuples( sizeVector );
  //      for ( i = 0 ; i < sizeVector; i++)
  //      {  tubeRadius->SetTuple1(i, 20);
  //      }
  //      polydata->GetPointData()->AddArray(tubeRadius);
  //      polydata->GetPointData()->SetActiveScalars("TubeRadius");


		int pointNum;
		pointNum = polydata->GetNumberOfPoints();

		vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
		scalars->SetName("Color");
		int numSequence;

		/// Add scalar to point;
		for (numSequence = 0; numSequence < pointNum; numSequence++)
		{
			scalars->InsertTuple1
			(numSequence, 0.5);
		}
		polydata->GetPointData()->SetScalars(scalars);

		/// Set vtkTranform and vtkTransformPloyDataFilter;
		vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		trans->RotateX(90);

		transFilter->SetInputData(polydata);
		transFilter->SetTransform(trans);

		//      vtkSmartPointer<vtkPolyData> transformedOutputPolydata =
		//         vtkPolyData::SafeDownCast( transFilter->GetOutput() );

		vtkSmartPointer<vtkPolyData> transformedOutputPolydata = transFilter->GetOutput();
		//      outputPolydata = transFilter->GetOutput();

			  /// Tube
		vtkSmartPointer<vtkTubeFilter> tube
			= vtkSmartPointer<vtkTubeFilter>::New();
		tube->SetInputData(transformedOutputPolydata);
		tube->SetNumberOfSides(8);
		tube->CappingOn();
		tube->SetRadius(2);
		//tube->SetVaryRadiusToVaryRadiusByAbsoluteScalar();

		/// Add transFilter to vtkAppendPolyData pointer everytime;
		append->AddInputConnection(tube->GetOutputPort());

		//      /// Add polydata to vtkAppendPolyData pointer everytime;
		//      append->AddInput( polydata );
	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}


void rsEpiCortexEndoWaterPathDBVisual::SymplastTubeXMLVtp(rsEpiCortexEndoWaterPathDB* RsEpiCortexEndoWaterPathDB)
{  /// declare iterator;
	map<int, vector<double> >::iterator itMapX;
	map<int, vector<double> >::iterator itMapY;
	map<int, vector<double> >::iterator itMapZ;
	vector<double>::iterator itVecX;
	vector<double>::iterator itVecY;
	vector<double>::iterator itVecZ;
	int i;
	int sizeVector;

	int epiPosition;

	//   ofstream fout("WaterPath.txt",ios::app);
	//   fout << "SymplastTubeXMLVtp" << endl;

	   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
	vtkSmartPointer<vtkAppendPolyData> append =
		vtkSmartPointer<vtkAppendPolyData>::New();
	vtkSmartPointer<vtkXMLPolyDataWriter> writer =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	string flName = getFolderName() + RsEpiCortexEndoWaterPathDB->SymplastXMLVtpFileName;
	writer->SetFileName(flName.c_str());
	addToFileNamesVector(RsEpiCortexEndoWaterPathDB->SymplastXMLVtpFileName);

	/// cout << circleSegmentLengthDB;
	for (itMapX = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastXDB.begin(),
		itMapY = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastYDB.begin(),
		itMapZ = RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastZDB.begin(), epiPosition = 0;
		itMapX != RsEpiCortexEndoWaterPathDB->epiCortexEndoSymplastXDB.end();
		itMapX++, itMapY++, itMapZ++, epiPosition++)
	{
		sizeVector = (itMapX->second).size();
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		vtkSmartPointer<vtkCellArray> lines =
			vtkSmartPointer<vtkCellArray>::New();
		lines->InsertNextCell(sizeVector);

		for (itVecX = (*itMapX).second.begin(),
			itVecY = (*itMapY).second.begin(),
			itVecZ = (*itMapZ).second.begin(), i = 0;
			itVecX != (*itMapX).second.end();
			itVecX++, itVecY++, itVecZ++, i++)
		{
			points->InsertNextPoint(*itVecX, *itVecY, *itVecZ);
			lines->InsertCellPoint(i);
			//         fout << "epiPosition: " << epiPosition << " ringNum: " << i
			//              << "  itVecX: " << *itVecX
			//              << "  itVecY: " << *itVecY
			//              << "  itVecZ: " << *itVecZ << endl;
		}

		// Extract the polydata
		vtkSmartPointer<vtkPolyData> polydata =
			vtkSmartPointer<vtkPolyData>::New();
		polydata->SetPoints(points);
		polydata->SetLines(lines);

		/// Set Scalars;
		int pointNum;
		pointNum = polydata->GetNumberOfPoints();

		vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
		scalars->SetName("Color");
		int numSequence;

		/// Add scalar to point;
		for (numSequence = 0; numSequence < pointNum; numSequence++)
		{
			scalars->InsertTuple1
			(numSequence, 0.2);
		}
		polydata->GetPointData()->SetScalars(scalars);

		/// Set vtkTranform and vtkTransformPloyDataFilter;
		vtkSmartPointer<vtkTransform> trans =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		trans->RotateX(90);

		transFilter->SetInputData(polydata);
		transFilter->SetTransform(trans);

		vtkSmartPointer<vtkPolyData> transformedOutputPolydata = transFilter->GetOutput();

		/// Tube
		vtkSmartPointer<vtkTubeFilter> tube
			= vtkSmartPointer<vtkTubeFilter>::New();
		tube->SetInputData(transformedOutputPolydata);
		tube->SetNumberOfSides(8);
		tube->CappingOn();
		tube->SetRadius(2);
		//tube->SetVaryRadiusToVaryRadiusByAbsoluteScalar();

		/// Add transFilter to vtkAppendPolyData pointer everytime;
		append->AddInputConnection(tube->GetOutputPort());

	}
	writer->SetInputConnection(append->GetOutputPort());
	writer->Write();
}
