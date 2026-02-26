#include "AABB.h"

const FAABB FAABB::Empty = FAABB(FInterval::Empty, FInterval::Empty, FInterval::Empty);
const FAABB FAABB::Universe = FAABB(FInterval::Universe, FInterval::Universe, FInterval::Universe);
