'use strict';

// 判断浏览器是否支持这些 API
if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) {
    console.log("enumerateDevices() not supported.");
}

var videoId = '';
// 枚举 cameras and microphones.
navigator.mediaDevices.enumerateDevices()
    .then(function(deviceInfos) {

        // 打印出每一个设备的信息
        deviceInfos.forEach(function(deviceInfo) {
            console.log(deviceInfo.kind + ": " + deviceInfo.label +
                " id = " + deviceInfo.deviceId);
            if(deviceInfo.kind === 'videoinput') {
                videoId = deviceInfo.deviceId
                alert(videoId)
                if(videoId.length > 0) {
                    let mediaStreamContrains = {
                        video: {
                            deviceId: videoId,
                            // facingMode: "user",
                            width: 320,
                            height: 200
                        },
                        audio: true
                    }
                    startVideo(mediaStreamContrains)
                } else {
                    let mediaStreamContrains = {
                        video: true,
                        audio: true
                    }
                    startVideo(mediaStreamContrains)
                }

            }
        });
    })
    .catch(function(err) {
        console.log(err.name + ": " + err.message);
    });


const localVideo = document.querySelector('video');

function gotLocalMediaStream(mediaStream){
    console.log('navigator.getUserMedia success');
    // window.webkit.messageHandlers.logger.postMessage('navigator.getUserMedia success')
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error){
    alert('navigator.getUserMedia error: '+ error.message)
    // window.webkit.messageHandlers.logger.postMessage(error.message)
    console.log('navigator.getUserMedia error: ', error.message);
}


function startVideo(mediaStreamContrains) {
    navigator.mediaDevices.getUserMedia(mediaStreamContrains).then(
        gotLocalMediaStream
    ).catch(
        handleLocalMediaStreamError
    );
}
// navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.mediaDevices.getUserMedia;






