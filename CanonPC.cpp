#include<iostream>
#include<EDSDK.h>
#include<EDSDKErrors.h>
#include<EDSDKTypes.h>

using namespace std;

EdsError getCanonCamera(EdsCameraRef *camera) {
	// Function to get the camera
	EdsError err;
	EdsCameraListRef camList;
	EdsUInt32 count = 0;

	err = EdsGetCameraList(&camList);
	if (err == EDS_ERR_OK) {
		err = EdsGetChildCount(camList,&count);
		if(count == 0) {
			err = EDS_ERR_DEVICE_NOT_FOUND;
			cout<<"No cameras found\n";
		}
	}
	cout<<"Number of cameras: "<<count<<endl;
	if(err == EDS_ERR_OK) {
		err = EdsGetChildAtIndex(camList,0,camera);
	}
	if(camList != NULL) {
		EdsRelease(camList);
		camList = NULL;
	}
	return err;
}

EdsError startLiveView(EdsCameraRef camera) {
	// Function to start the live view on the camera
	EdsError err;
	EdsUInt32 device;
	err =	EdsGetPropertyData(camera,kEdsPropID_Evf_OutputDevice,0,sizeof(device),&device);
	if(err == EDS_ERR_OK) {
		device|= kEdsEvfOutputDevice_PC;
		err = EdsSetPropertyData(camera,kEdsPropID_Evf_OutputDevice,0,sizeof(device),&device);
	}
	return err;
}

EdsError startRecording(EdsCameraRef camera) {
	// Function to start recording video
	EdsError err;
	EdsUInt32 record_start = 4; // Begin movie shooting 
	err = EdsSetPropertyData(camera, kEdsPropID_Record, 0, sizeof(record_start), &record_start); 
	return err;
}

EdsError stopRecording(EdsCameraRef camera) {
	//Function to stop recording video
	EdsError err;
	EdsUInt32 record_stop = 0; // End movie shooting 
	err = EdsSetPropertyData(camera, kEdsPropID_Record, 0, sizeof(record_stop), &record_stop);
	return err;
}

EdsError setCameraAsDestination(EdsCameraRef camera) {
	//Function to set the camera's sd as save target
	EdsError err;
	EdsUInt32 saveTo = kEdsSaveTo_Camera;
	err = EdsSetPropertyData(camera,kEdsPropID_SaveTo,0,sizeof(saveTo),&saveTo);
	return err;
}

EdsError takePicture(EdsCameraRef camera) {
	// Function to capture picture
	EdsError err;
	err = EdsSendCommand(camera,kEdsCameraCommand_PressShutterButton,0);
	cout<<"Picture captured\n";
	return err;
}

int main() {
	EdsError err = EDS_ERR_OK;
	EdsCameraRef camera = NULL;

	err = EdsInitializeSDK();
	if(err == EDS_ERR_OK) {
		cout<<"SDK initialized\n";
	} else 
		cout<<"SDK not initialized\n";
	
	if(err == EDS_ERR_OK)
		err = getCanonCamera(&camera);
	
	if(err == EDS_ERR_OK) 
		err = EdsOpenSession(camera);
	if(err == EDS_ERR_OK)
		err = setCameraAsDestination(camera);
	err = EdsSendStatusCommand(camera,kEdsCameraStatusCommand_UIUnLock,0);
	//err = takePicture(camera);
	err = startLiveView(camera);
	cout<<"Press enter to start recording\n";
	getchar();
	if(err == EDS_ERR_OK) {
		err = startRecording(camera);
		if(err != EDS_ERR_OK) {
			cout<<"Make sure the camera is in movie shooting mode\n";
		}
	}
	cout<<"Enter to stop recording";
	getchar();
	if(err == EDS_ERR_OK) {
		err = stopRecording(camera);
		if(err != EDS_ERR_OK) {
			cout<<"Not able to stop! Switch off the camera\n";
		}
	}

	if(err == EDS_ERR_OK) {
		err = EdsCloseSession(camera);
	}

	if(camera != NULL) 
		EdsRelease(camera);
	EdsTerminateSDK();
	if(err != EDS_ERR_OK)
		cout<<"ERROR\n";
	getchar();
	return 0;
}