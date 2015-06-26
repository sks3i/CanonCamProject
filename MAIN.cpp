#include "canonCam.h"

EdsError initialize(EdsCameraRef *camera) {
	EdsError err = EDS_ERR_OK;
	err = EdsInitializeSDK();
	if(err == EDS_ERR_OK)
		cout<<"SDK initialized\n";
	else {
		cout<<"SDK not initialized\n";
		getchar();
		exit(-1);
	}
	if(err == EDS_ERR_OK)
		err = getCamera(camera);
	if(err == EDS_ERR_OK) 
		err = EdsOpenSession(*camera);
	return err;
}

void exitProperly(EdsCameraRef *camera) {
	EdsError err;
	err = EdsCloseSession(*camera);
	if(camera != NULL) 
		EdsRelease(*camera);
	EdsTerminateSDK();
	if(err != EDS_ERR_OK)
		cout<<"ERROR\n";
}

int main() {
	int choice;
	EdsError err;
	EdsCameraRef camera;
	err = initialize(&camera);
MENU:
	cout<<"MENU:\n";
	cout<<"1. Take picture\n";
	cout<<"2. Record video\n";
	cout<<"3. Exit\n";
	cout<<"Enter 1/2/3 to select: ";
	cin>>choice;

	switch(choice) {
	case 1:
		err = takePicture(camera);
		if(err != EDS_ERR_OK) {
			cout<<"Error while taking photo\n";
			getchar();
			exit(-1);
		}
		break;
	case 2:
		err = startLiveView(camera);
		cout<<"Press 'ENTER' to start recording\n";
		if(err == EDS_ERR_OK) err = startRecording(camera);
		if(err != EDS_ERR_OK) {
			cout<<"ERROR: Not able to start recording! Make sure the camera is in movie shooting mode\n";
			getchar();
			exit(-1);
		}
		cout<<"Press 'ENTER' to stop recording\n";
		err = stopRecording(camera);
		if(err != EDS_ERR_OK) {
			cout<<"ERROR: Not able to stop recording! Switch off the camera manually\n";
			getchar();
			exit(-1);
		}
	case 3:
		exit(-1);
	default:
		cout<<"Wrong choice!\n\n\n";
		goto MENU;
	}
	exitProperly(&camera);
	getchar();
}