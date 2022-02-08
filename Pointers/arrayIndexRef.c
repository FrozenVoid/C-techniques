Idiom:
type ptr=(ptr*)& otherPtr[5];

this uses otherPtr+5 (as ptr[0]) without
invoking pointer arithmethic,
which in complex expression will
prove hard to debug.
