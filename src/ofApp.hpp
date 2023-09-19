#pragma once

#include "AudioVisualizer.hpp"
#include "ofMain.h"
#include <string>

class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;

    
    bool songShuffle= false;
    bool playing = false;
    bool ampUpdate = true;
    double volUpdate = 1;
    int songIndex = 0;
    bool songLoop = false;
    bool songRepeat = false;
    string modeStr;
    char mode = '1';

    int cur_x, cur_y = 0;
    float sound_length;

    float progress = 0;
    float lastPos = 0;
    int NewX=0; // esto fue lo que cambie
    int NewY=ofGetHeight() - 60; // punto de y donde empieza la barra de progreso
    int PbarH=20; //altura de la barra
    float pos = playing ? progress : lastPos;
    int percent = pos * 100; //la puse global
    float PbarW= ofGetWidth(); //largo de la barra

  public:
    void setup();
    void update();
    void draw();

    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
