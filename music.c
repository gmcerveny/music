#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"

const char *noteDescriptions[] = 
  {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

int musicMakeMiddleNote(notename name) {
  return musicMakeNote(name, 5);
};

int musicMakeNote(notename name, int octave) {
  return name + octave * 12;
}

int sizeOfScale(musicMode mode) {
  switch (mode){
    case ionian:
    case aeolian:
    {
      return 7;
      break;
    }
    case pentatonicMinor:
    {
      return 5;
    }
  }
  return 0;
}

// TODO: create midiNote alias to differentiate between
// TODO: create and allocate array within musicMakeScale function
void musicMakeScale(notename root, musicMode mode, int * notes) {
  musicSteps * sequence;

  switch (mode){
    case ionian:
    {
      musicSteps ionianSequence[7] = {T,T,S,T,T,T,S};
      sequence = ionianSequence;
      break;
    }
    case aeolian:
    {
      musicSteps aeolianSequence[7] = {T,S,T,T,S,T,T};
      sequence = aeolianSequence;
      break;
    }
    case pentatonicMinor:
    {
      musicSteps pentatonicMinorSequence[5] = {T+S,T,T,T+S,T};
      sequence = pentatonicMinorSequence;
      break;
    }
  }

  notes[0] = musicMakeMiddleNote(root);
  for (int i = 1; i < sizeOfScale(mode); i++) {
    notes[i] = notes[i-1] + sequence[i-1];
  }
}


void musicMakeChordFromScale(int * scale, int size, int degree, int * chord)
{
  int degreeIndex = degree - 1;
  for (int i = 0; i < 3; i++, degreeIndex += 2){
    div_t q = div(degreeIndex, size);
    chord[i] = scale[q.rem] + 12 * q.quot;
  }
}

// TODO: chord modes (major,minor,7th,...)
void musicMakeChordFromKey(notename key, musicMode mode, int degree, int * chord)
{
  int size = sizeOfScale(mode);
  int scale[size];
  musicMakeScale(key, mode, scale);

  musicMakeChordFromScale(scale, size, degree, chord);
}

notename midiNoteName(int note) {
  return note % 12;
}

const char * stringFromNotename(notename note) {
  return noteDescriptions[note];
}

const char * stringFromMIDINote(int note) {
  return stringFromNotename(midiNoteName(note));
}

void printNotes(int * notes, int count) { 
  printf("--------\n");
  for (int i = 0; i < count; i++) {
    printf("%s\tMIDI: %d\n", stringFromMIDINote(notes[i]), notes[i]);
  }
  printf("--------\n");
}

notename notenameFromString(char *string) {
  for (int i = 0; i < 12; i++) {
    if (strcmp(string, noteDescriptions[i]) == 0) return i;
  }
  return -1;
}

int main(int argc, char **argv) {
  int root = C;
  if (argc > 1) root = notenameFromString(argv[1]);
  
  musicMode mode = naturalMinor;
  int size = sizeOfScale(mode);
  int scale[size];
  musicMakeScale(root, mode, scale);
  printNotes(scale, size);

  int chord[3];
  for (int i = 1; i <= size; i++){
    musicMakeChordFromScale(scale, size, i, chord);
    printNotes(chord,3);
  }
}