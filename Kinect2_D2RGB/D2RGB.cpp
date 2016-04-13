#include <iostream>
#include <vector>
#include <fstream>
#define NOMINMAX
#include <Windows.h>
#include <Kinect.h>

using namespace std;

int main() {

	HRESULT result;
	IKinectSensor* sensor;
	ICoordinateMapper* mapper;

	// Create Sensor Instance
	result = GetDefaultKinectSensor(&sensor);
	if (FAILED(result)) {
		cerr << "GetDefaultKinectSensor() failed." << endl;
		return 0;
	}

	// Open Sensor
	result = sensor->Open();
	if (FAILED(result)) {
		cerr << "IKinectSensor::Open() failed." << endl;
		return 0;
	}

	// Retrieved Coordinate Mapper
	result = sensor->get_CoordinateMapper(&mapper);
	if (FAILED(result)) {
		cerr << "IKinectSensor::get_CoordinateMapper() failed." << endl;
		return 0;
	}

	vector<CameraSpacePoint> camera_points;

	//read camera_space points

	ifstream infile("test.txt");
	CameraSpacePoint p;

	while (!infile.eof()) {
		infile >> p.X >> p.Y >> p.Z;
		camera_points.push_back(p);
	}
	infile.close();

	cerr << "Camera Points" << endl;
	for (unsigned int i = 0; i < camera_points.size(); i++)
		cerr << camera_points[i].X << ", " << camera_points[i].Y << ", " << camera_points[i].Z << endl;

	vector<ColorSpacePoint> color_points(camera_points.size());

	result = mapper->MapCameraPointsToColorSpace((UINT)camera_points.size(), &camera_points[0], (UINT)color_points.size(), &color_points[0]);
	if (FAILED(result)) {
		cerr << "ICoordinateMapper::MapCameraPointsToColorSpace() failed." << endl;
		return 0;
	}

	//write color_space points

	cerr << "Camera Points" << endl;
	for (unsigned int i = 0; i < color_points.size(); i++)
		cerr << color_points[i].X << ", " << color_points[i].Y << endl;

	return 0;
}
