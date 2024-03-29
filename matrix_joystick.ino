

/* 
8x8 led matrix sxxxxx
 
rows are the anodes
cols are the cathodes

 _________
 col 4  ----|         |---- row n
 col 2  ----|         |---- row n
 row 7  ----|         |---- col 7
 row 6  ----|         |---- row 8
 col 1  ----|         |---- col 5
 row 4  ----|         |---- row 3
 col 3  ----|         |---- row 5  
 col 6  ----|         |---- col 8
 ---------
 
 */
 
// max and min values from the accelerometer, 
// found by experiment:
const int sensorXmin = 20;
const int sensorXmax = 900;
const int sensorMin = 20;
const int sensorMax = 900;

// 2-dimensional array of row pin numbers (for two matrices):
const int row[8] = {
  13,17,9,10,2,8,3,6  };

// 2-dimensional array of column pin numbers (for two matrices):
const int col[8] = {
  16,4,5,12,7,11,18,19  };

// 2-dimensional array of pixels:
int pixels[8][8];           

// cursor position:
int x = 7;
int y = 6;
int zx = 8;
int zy = 7;

void setup() {
  Serial.begin(9600);
  // initialize the I/O pins as outputs:

  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();

}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = HIGH;
   pixels[zx][y] = HIGH;
  pixels[x][zy] = HIGH;
  pixels[zx][zy] = HIGH;
//  y = analogRead(0);
//  x = analogRead(1);
  //  Serial.println(x);
 // Serial.println(" ");
  //Serial.println(y);
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(0), sensorMin, sensorMax, 7, 0);
  y = map(analogRead(1), sensorXmin, sensorXmax, 0, 7);
/*  y = 7 - map(analogRead(0), sensorMin, sensorMax, 7, 0);
  x = map(analogRead(1), sensorMin, sensorMax, 7, 0); */
  zx = x + 1;
  zy = y + 1;
    zx = x + 1;
  zy = y + 1;
  if ( x == 0 ) {
    zx = 1;
  }
  if ( x == 7) {
    zx = 6;
  }
  if ( y == 0 ) {
    zy = 1;
  }
  if ( y == 7 ) {
    zy = 6;
  }
  pixels[x][y] = LOW;
  pixels[zx][y] = LOW;
  pixels[x][zy] = LOW;
  pixels[zx][zy] = LOW;
 // Serial.println(x);
  //Serial.println(" ");
  //Serial.println(y);

}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }

    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }

}

