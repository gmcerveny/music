#ifndef music
#define music

// pitch

typedef enum {
  C = 0,
  Cs = 1, Db = 1,
  D = 2,
  Ds = 3, Eb = 3,
  E = 4,
  F = 5,
  Fs = 6, Gb = 6,
  G = 7,
  Gs = 8, Ab = 8,
  A = 9,
  As = 10, Bb = 10,
  B = 11
} notename;

int musicMakeMiddleNote(notename name);
int musicMakeNote(notename name, int octave);

// key

// TODO: add pentatonic

typedef enum {
  ionian = 0,
  major = 0,
  aeolian = 1,
  naturalMinor = 1
} musicMode;

typedef enum {
  S = 1, // semitone
  half = 1,
  T = 2, // tone
  whole = 2
} musicSteps;

void musicMakeScale(notename root, musicMode mode, int * notes);


// duration

// notes

struct note {
  notename name;
  int octave;
  int midi;
};

#endif