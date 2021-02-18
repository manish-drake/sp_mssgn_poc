import QtQuick 2.9
import QtMultimedia 5.4
import "camera-qml"

Rectangle {
    id : cameraUI
    property int vm_state: vm.state
    width: 800
    height: 480

    color: "black"
    state: "VideoCapture"
    onVm_stateChanged: {
        if(vm_state ===1)
        {
            console.log("Start recording")
            camera.videoRecorder.record()
        }
        else{
            console.log("Stop recording")
            camera.videoRecorder.stop()
        }
    }

    states: [
        State {
            name: "PhotoCapture"
            StateChangeScript {
                script: {
                    camera.captureMode = Camera.CaptureStillImage
                    camera.start()
                }
            }
        },
        State {
            name: "PhotoPreview"
        },
        State {
            name: "VideoCapture"
            StateChangeScript {
                script: {
                    camera.captureMode = Camera.CaptureVideo
                    camera.start()
                }
            }
        },
        State {
            name: "VideoPreview"
            StateChangeScript {
                script: {
                    camera.stop()
                }
            }
        }
    ]

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage

        imageCapture {
            onImageCaptured: {
                photoPreview.source = preview
                stillControls.previewAvailable = true
                cameraUI.state = "PhotoPreview"
            }
        }

        videoRecorder {
             resolution: "640x480"
             frameRate: 30
        }
    }

    PhotoPreview {
        id : photoPreview
        anchors.fill : parent
        onClosed: cameraUI.state = "PhotoCapture"
        visible: cameraUI.state == "PhotoPreview"
        focus: visible
    }

    VideoPreview {
        id : videoPreview
        anchors.fill : parent
        onClosed: cameraUI.state = "VideoCapture"
        visible: cameraUI.state == "VideoPreview"
        focus: visible

        //don't load recorded video if preview is invisible
        source: visible ? camera.videoRecorder.actualLocation : ""
    }

    VideoOutput {
        id: viewfinder
        visible: cameraUI.state == "PhotoCapture" || cameraUI.state == "VideoCapture"

        x: 0
        y: 0
        width: parent.width - stillControls.buttonsPanelWidth
        height: parent.height

        source: camera
        autoOrientation: true
    }

    PhotoCaptureControls {
        id: stillControls
        anchors.fill: parent
        camera: camera
        visible: cameraUI.state == "PhotoCapture"
        onPreviewSelected: cameraUI.state = "PhotoPreview"
        onVideoModeSelected: cameraUI.state = "VideoCapture"
    }

    VideoCaptureControls {
        id: videoControls
        anchors.fill: parent
        camera: camera
        visible: cameraUI.state == "VideoCapture"
        onPreviewSelected: cameraUI.state = "VideoPreview"
        onPhotoModeSelected: cameraUI.state = "PhotoCapture"
    }
}
