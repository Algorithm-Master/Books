'use strict';

// 判断浏览器是否支持这些 API
if (!navigator.mediaDevices || !navigator.mediaDevices.enumerateDevices) {
    console.log("enumerateDevices() not supported.");
}

let videoId = '';
// 枚举 cameras and microphones.
navigator.mediaDevices.enumerateDevices()
    .then(function(deviceInfos) {

        // 打印出每一个设备的信息
        deviceInfos.forEach(function(deviceInfo) {
            console.log(deviceInfo.kind + ": " + deviceInfo.label +
                " id = " + deviceInfo.deviceId);
            if(deviceInfo.kind === 'videoinput') {
                videoId = deviceInfo.deviceId
            }
        });
    })
    .catch(function(err) {
        console.log(err.name + ": " + err.message);
    });

const mediaStreamContrains = {
    video: {
        deviceID: videoId,
        // facingMode: "user",
        width: 320,
        height: 200
    },
    audio: true
};

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

console.log('get play devices ', navigator.mediaDevices.enumerateDevices())
// navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.mediaDevices.getUserMedia;

navigator.mediaDevices.getUserMedia(mediaStreamContrains).then(
    gotLocalMediaStream
).catch(
    handleLocalMediaStreamError
);
