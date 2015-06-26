#include<iostream>
#include<EDSDK.h>
#include<EDSDKErrors.h>
#include<EDSDKTypes.h>

using namespace std;

EdsError getCamera(EdsCameraRef *camera);
EdsError startLiveView(EdsCameraRef camera);
EdsError startRecording(EdsCameraRef camera);
EdsError stopRecording(EdsCameraRef camera);
EdsError setCameraAsDestination(EdsCameraRef camera);
EdsError takePicture(EdsCameraRef camera);