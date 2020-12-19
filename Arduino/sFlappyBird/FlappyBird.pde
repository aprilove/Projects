import processing.serial.*; // import processing serial stuff

Serial mySerial; // serial object

String myString = null; // to store things from serial
int nl = 10; // new line ASCII
PImage backImg =loadImage("https://i.imgur.com/UfT935e.png"); // background found from my imgur
int gameState = 1; // gameState 
int score = 0; // score
float x = -200; // x location
float y, ay = 0; // y location and acceleration y
float bSize = 20; // size
int minGH = 200; // gap heights
int maxGH = 300; // gap heights
int wWidth = 80; // wall widths
int wSpeed = 5; // speed of wall
int wInterval = 1000; // interval
float LAT = 0; // to find when to add a new wall
color wColors = color(34, 139, 34); // color
color bColor = color(212, 175, 55); // color
ArrayList<int[]> walls = new ArrayList<int[]>(); // arraylist to hold information about walls 

//set up
void setup() {
  size(600, 800); //screen size
  fill(0); // bg
  String myPort = Serial.list() [0]; // define serial port
  mySerial = new Serial (this, myPort, 9600); // define object
}

//draw
void draw () {
  // if game is running
  if (gameState ==0) {
    imageMode(CORNER);
    //illusion that ball moves by moving bg
    image(backImg, x, 0);
    image(backImg, x+backImg.width, 0);
    x -= 4;
    //draw ball
    drawBall();
    // limit
    if (x == -1800) 
      x = 0;
    // ball acceleration
    acceleration();
    // walls
    wallAdder();
    wallHandler();
    // score
    printScore();
    // collision with bounds
    keepInScreen();
    // input from button
    input();
  } else { // if game not running

    startText();
    imageMode(CENTER);
    input();
  }
}
void startText() {
  // display text
  textAlign(CENTER);
  fill(0, 102, 153);
  textSize(70);
  text("click to start", 300, 300);
}

void gameOver() {
  // change gameState when game is over to game not running
  gameState = 1;
  // save memory by clearing
  walls.clear();
  // reset variables
  y = height/2;
  x = score = 0;
  ay = 0;
}

void drawBall() {
  // draws the ball...
  fill(bColor);
  ellipse(width/2, y, bSize, bSize);
}

void acceleration() {
  // accelerates the ball
  ay+=0.2;
  y+=ay;
}

void wallAdder() {
  // generates a wall on wInterval
  if (millis()-LAT > wInterval) {
    int randH = round(random(minGH, maxGH));
    int randY = round(random(0, height-randH));
    int[] randWall = {width, randY, wWidth, randH, 0}; 
    walls.add(randWall);
    LAT = millis();
  }
}
void wallHandler() {
  // runs wall handler for all walls in the arraylist
  // could save memory here by ignoring the other walls on screen except first but... its like 70mb or something 
  for (int i = 0; i < walls.size(); i++) {
    wallRemover(i);
    wallMover(i);
    wallDrawer(i);
    watchWallCollision(i);
  }
}
void wallDrawer(int index) {
  // draws walls
  int[] wall = walls.get(index);
  noStroke();
  fill(wColors);
  rect(wall[0], 0, wall[2], wall[1]);
  rect(wall[0], wall[1]+wall[3], wall[2], height-(wall[1]+wall[3]));
}
void wallMover(int index) {
  // moves the walls
  int[] wall = walls.get(index);
  wall[0] -= wSpeed;
}
void wallRemover(int index) {
  // removes the wall
  int[] wall = walls.get(index);
  if (wall[0]+wall[2] <= 0) {
    walls.remove(index);
  }
}
void watchWallCollision(int index) {
  // finds if wall and ball have collided
  int[] wall = walls.get(index);
  int wallScore = wall[4];
  int wallBX = wall[0];
  int wallBY = wall[1]+wall[3];
  int wallBW = wall[2];
  int wallBH = height-(wall[1]+wall[3]);
  int wallTW = wall[2];
  int wallTH = wall[1];

  //if collided with top wall
  if ((width/2+(bSize/2)>wall[0]) && (width/2-(bSize/2)<wall[0]+wallTW) &&(y+(bSize/2)>0) && (y-(bSize/2)<0+wallTH)) 
    gameOver();
  // if collided with bottom wall
  if ((width/2+(bSize/2)>wallBX) && (width/2-(bSize/2)<wallBX+wallBW) && (y+(bSize/2)>wallBY) && (y-(bSize/2)<wallBY+wallBH)) 
    gameOver();
  // if passed wall
  if (width/2 > wall[0]+(wall[2]/2) && wallScore==0) {
    wallScore=1;
    wall[4]=1;
    score();
  }
}

void keepInScreen() {
  // ball hits floor
  if (y+(bSize/2) > height) { 
    gameOver();
  }
  // ball hits ceiling
  if (y-(bSize/2) < 0) {
    gameOver();
  }
}

void score() {
  score++;
}

void printScore() {
  // prints score
  textAlign(CENTER);
  fill(0);
  textSize(30); 
  text(score, height/2, 70);
}

// in the case you would want to play with a mouse
void mousePressed() {
  ay=-5;
  if (gameState==1) {
    y = height/2;
    gameOver();
  }
}

//arduino input
void input() {
  // if arduino is sending
  while (mySerial.available() > 0) {
    // read the string 
    myString = mySerial.readStringUntil(nl);
    // if something was sent
    if (myString != null) {
      ay=-5;
      // to start game from gameover screen
      if (gameState==1) {
        gameOver();
        gameState = 0;
      }
    }
  }
}
