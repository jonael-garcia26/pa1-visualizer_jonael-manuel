#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    string songs[] = {"beat.wav","geesebeat.wav","pigeon-coo.wav","rock-song.wav"};
    sound.load(songs[songIndex]);           // Loads a sound file (in bin/data/)
    sound.setLoop(false);              // Makes the song loop indefinitely
    sound.setVolume(volUpdate);               // Sets the song volume
    ofSetBackgroundColor(36, 32, 56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();                   // Updates all sound players
      if (ampUpdate){   // actualiza las amplitudes solo si ampUpdate es true (cambia el valor al precionar 'd')
       visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    progress = sound.getPosition();
    if (songLoop && sound.getPosition() >= 0.99)       // cambia las canciones en orden cuando acaban cuando el modo Loop esta activo
    {
       if (songIndex < 3)
       {
           songIndex++;
           setup();
           sound.play();
       }
       else
       {
           songIndex = 0;
           setup();
           sound.play();
       }
    }

    if (songRepeat && sound.getPosition() >= 0.99){
        sound.setLoop(true);
    } else {
        sound.setLoop(false);
    }
    sound.setVolume(volUpdate);     // Se actualiza el volumen con '-' o '='

    if (songShuffle  && sound.getPosition() >=0.99){
        int random = ofRandom(0,4);
        while (songIndex == random)
        {
            random = ofRandom(0,4);
            if (songIndex != random){
                break;
            }
        }
        songIndex = random;
        setup();
        sound.play();
    }
   
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(255,0,0);
    ofFill();
    ofDrawRectangle(0, ofGetHeight() - 60, (progress*ofGetWidth()), 20);
        
    ofSetColor(255);
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    //ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), ofGetWidth() / 2 - 50, 15);
    ofDrawBitmapString("Press '=' to turn UP the volume", 0, 45);
    ofDrawBitmapString("Press '-' to turn DOWN the volume", 0, 60);
    ofDrawBitmapString("Press 'a' to pause the visualizer", 0, 75);
    ofDrawBitmapString("Press 'd' to change the song", 0, 90);
    ofDrawBitmapString("Press 'l' for Loop mode", 0, 105);
    ofDrawBitmapString("Press 'r' for Repeat mode", 0, 120);
    ofDrawBitmapString("Press 'b' for Shuffle mode", 0, 135);
    if (songLoop)
    {
       ofDrawBitmapString("Loop mode is active", ofGetWidth() / 2 - 50, 15);
    }
    else if (songRepeat)
    {
       ofDrawBitmapString("Repeat mode is active", ofGetWidth() / 2 - 50, 15);
    } else if (songShuffle){
       ofDrawBitmapString("Shuffle mode is active", ofGetWidth() / 2 - 50, 15);
    }
    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    }

}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0, 0, ofRandom(255));
    ofSetBackgroundColor(255, 153, 51);
    for (int i=0;i<=64; i++){ //en la primera i tengo que poner tambien un loop que vaya cambiando las D
        ofDrawRectRounded(i*(ofGetWidth()/64), ofGetHeight() - 100, ofGetWidth()/64, amplitudes[i], 10);//estoy haciendo cambiando las amplitudes con ese for loop, cada bar va mas 1 
    }
}
void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofSetBackgroundColor(102, 204, 0);
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetLineWidth(5);
    ofFill();
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Circles Row Visualizer", 0, 15);
    ofSetColor(255, 255, 0);
    ofSetBackgroundColor(204, 0, 204);
    for (int i = 0; i < 64; i++){
            ofDrawCircle(ofGetWidth() / 64 * i, ofGetHeight() / 2,  amplitudes[i]);
    }

    // YOUR CODE HERE
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case 'a':
        ampUpdate = !ampUpdate;
        break;
    case 'd':
        if (songIndex < 3){
            songIndex++;
            setup();
            sound.play();
        } else {
            songIndex = 0;
            setup();
            sound.play();
        }
        break;
    case 'r':
        songLoop = false;
        songShuffle = false;
        songRepeat = !songRepeat;
        break;
    case 'l':
        songRepeat = false;
        songShuffle = false;
        songLoop = !songLoop;
        break;
    case 'b':
        songLoop = false;
        songRepeat = false;
        songShuffle = !songShuffle;
        break;
    case '=':
    if (volUpdate < 1){
        volUpdate = volUpdate + 0.1;
        break;
    } else {
         break;
    }
    case '-':
    if (volUpdate > 0){
        volUpdate = volUpdate - 0.1;
        break;
    } else {
         break;
    }

        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    }

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if(x>=NewX && x<=NewX+PbarW && y>=NewY && y<=NewY+PbarH){
        percent=(x-NewX)/PbarW;
        sound.setPosition(x/PbarW);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------