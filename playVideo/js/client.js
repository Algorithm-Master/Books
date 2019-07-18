'use strict';

const mediaStreamContrains = {
    video: {
        facingMode: "environment",
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

navigator.getUserMedia = navigator.getUserMedia ||
    navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.mediaDevices.getUserMedia;

navigator.getUserMedia(mediaStreamContrains).then(
    gotLocalMediaStream
).catch(
    handleLocalMediaStreamError
);
