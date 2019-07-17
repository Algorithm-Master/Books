'use strict';

const mediaStreamContrains = {
    video: true
};

const localVideo = document.querySelector('video');

function gotLocalMediaStream(mediaStream){
    localVideo.srcObject = mediaStream;
}

function handleLocalMediaStreamError(error){
    alert('navigator.getUserMedia error: '+ error.message)
    console.log('navigator.getUserMedia error: ', error.message);
}

navigator.mediaDevices.getUserMedia(mediaStreamContrains).then(
    gotLocalMediaStream
).catch(
    handleLocalMediaStreamError
);
