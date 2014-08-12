#include <stdio.h>
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

notename midiNoteName(int note) {
  return note % 12;
}

const char * stringFromNotename(notename note) {
  return noteDescriptions[note];
}

// TODO: create string output for testing
const char * stringFromMIDINote(int note) {
  return stringFromNotename(midiNoteName(note));
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
  
  musicMode mode = pentatonicMinor;
  int count = sizeOfScale(mode);
  int notes[count];
  musicMakeScale(root, mode, notes);

  for (int i = 0; i < count; i++) {
    printf("%s\tdegree: %d\tnote: %d\n", stringFromMIDINote(notes[i]), i, notes[i]);
  }
}