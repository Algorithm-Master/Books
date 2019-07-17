'use strict';

const mediaStreamContrains = {
    video: true
};

const localVideo = document.querySelector('video');

function gotLocalMediaStream(mediaStream){
    console.log('navigator.getUserMedia success');
    window.webkit.messageHandlers.logger.postMessage('navigator.getUserMedia success')
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error){
    alert('navigator.getUserMedia error: '+ error.message)
    window.webkit.messageHandlers.logger.postMessage(error.message)
    console.log('navigator.getUserMedia error: ', error.message);
}

navigator.mediaDevices.getUserMedia(mediaStreamContrains).then(
    gotLocalMediaStream
).catch(
    handleLocalMediaStreamError
);
