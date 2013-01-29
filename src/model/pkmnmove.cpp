#include "pkmnmove.h"

PkmnMove::PkmnMove (int id, const string &name, byte element,
                    byte type, int pp, int power, int accuracy) :
  _id(id), _name(name), _element(element), _type(type), _pp(pp),
  _power(power), _accuracy(accuracy) { }

int PkmnMove::getId () const { return _id; }

string PkmnMove::getName () const { return _name; }

byte PkmnMove::getElement () const { return _element; }

byte PkmnMove::getType () const { return _type; }

int PkmnMove::getPP () const { return _pp; }

int PkmnMove::getPwr () const { return _power; }

int PkmnMove::getAcc () const { return _accuracy; }

const PkmnMove *PkmnMoveList::get (int index) {
  if (index < 0 || index > 165)
    return &_movesList[0];
  return &_movesList[index];
}

const PkmnMove *PkmnMoveList::get (const string &name) {
  for (int i=0; i<166; ++i) {
    if (_movesList[i].getName() == name)
      return &_movesList[i];
  }
  return &_movesList[0];
}

vector<const PkmnMove *> PkmnMoveList::getByElement(byte element) {
  vector<const PkmnMove *> result;
  for (int i=1; i<166; ++i) {
    if (_movesList[i].getElement() == element)
      result.push_back(&_movesList[i]);
  }
  return result;
}
vector<const PkmnMove *> PkmnMoveList::getByType(byte type) {
  vector<const PkmnMove *> result;
  for (int i=1; i<166; ++i) {
    if (_movesList[i].getType() == type)
      result.push_back(&_movesList[i]);
  }
  return result;
}

const PkmnMove PkmnMoveList::_movesList[] = {
  PkmnMove(  0, "NoMove"       , Element::NORMAL  , Type::PHYSICAL,  0,   0,   0),
  PkmnMove(  1, "Pound"        , Element::NORMAL  , Type::PHYSICAL, 35,  40, 100),
  PkmnMove(  2, "Karate Chop"  , Element::NORMAL  , Type::PHYSICAL, 25,  50, 100),
  PkmnMove(  3, "Double Slap"  , Element::NORMAL  , Type::PHYSICAL, 10,  15,  85),
  PkmnMove(  4, "Comet Punch"  , Element::NORMAL  , Type::PHYSICAL, 15,  18,  85),
  PkmnMove(  5, "Mega Punch"   , Element::NORMAL  , Type::PHYSICAL, 20,  80,  85),
  PkmnMove(  6, "Pay Day"      , Element::NORMAL  , Type::PHYSICAL, 20,  40, 100),
  PkmnMove(  7, "Fire Punch"   , Element::FIRE    , Type::PHYSICAL, 15,  75, 100),
	PkmnMove(  8, "Ice Punch"    , Element::ICE     , Type::PHYSICAL, 15,  75, 100),
	PkmnMove(  9, "Thunder Punch", Element::ELECTRIC, Type::PHYSICAL, 15,  75, 100),
	PkmnMove( 10, "Scratch"      , Element::NORMAL  , Type::PHYSICAL, 35,  40, 100),
	PkmnMove( 11, "Vice Grip"    , Element::NORMAL  , Type::PHYSICAL, 30,  55, 100),
	PkmnMove( 12, "Guillotine"   , Element::NORMAL  , Type::PHYSICAL,  5,   0, 100),
	PkmnMove( 13, "Razor Wind"   , Element::NORMAL  , Type::SPECIAL , 10,  80, 100),
	PkmnMove( 14, "Sword Dance"  , Element::NORMAL  , Type::STATUS  , 30,   0, 100),
	PkmnMove( 15, "Cut"          , Element::NORMAL  , Type::PHYSICAL, 30,  50,  95),
	PkmnMove( 16, "Gust "        , Element::FLYING  , Type::SPECIAL , 35,  40, 100),
	PkmnMove( 17, "Wing Attack"  , Element::FLYING  , Type::PHYSICAL, 35,  60, 100),
	PkmnMove( 18, "Whirlwind"    , Element::FLYING  , Type::STATUS  , 20,   0, 100),
	PkmnMove( 19, "Fly"          , Element::FLYING  , Type::PHYSICAL, 15,  90,  95),
	PkmnMove( 20, "Bind "        , Element::NORMAL  , Type::PHYSICAL, 20,  15,  85),
	PkmnMove( 21, "Slam "        , Element::NORMAL  , Type::PHYSICAL, 20,  80,  75),
	PkmnMove( 22, "Vine Whip"    , Element::GRASS   , Type::PHYSICAL, 15,  35, 100),
	PkmnMove( 23, "Stomp"        , Element::NORMAL  , Type::PHYSICAL, 20,  65, 100),
	PkmnMove( 24, "Double Kick"  , Element::FIGHTING, Type::PHYSICAL, 30,  30, 100),
	PkmnMove( 25, "Mega Kick"    , Element::NORMAL  , Type::PHYSICAL,  5, 120,  75),
	PkmnMove( 26, "Jump Kick"    , Element::FIGHTING, Type::PHYSICAL, 10, 100,  95),
	PkmnMove( 27, "Rolling Kick ", Element::FIGHTING, Type::PHYSICAL, 15,  60,  85),
	PkmnMove( 28, "Sand Attack"  , Element::GROUND  , Type::STATUS  , 15,   0, 100),
	PkmnMove( 29, "Headbutt"     , Element::NORMAL  , Type::PHYSICAL, 15,  70, 100),
	PkmnMove( 30, "Horn Attack"  , Element::NORMAL  , Type::PHYSICAL, 25,  65, 100),
	PkmnMove( 31, "Fury Attack"  , Element::NORMAL  , Type::PHYSICAL, 20,  15,  85),
	PkmnMove( 32, "Horn Drill"   , Element::NORMAL  , Type::PHYSICAL,  5,   0,   0),
	PkmnMove( 33, "Tackle"       , Element::NORMAL  , Type::PHYSICAL, 30,  50, 100),
	PkmnMove( 34, "Body Slam"    , Element::NORMAL  , Type::PHYSICAL, 15,  85, 100),
	PkmnMove( 35, "Wrap "        , Element::NORMAL  , Type::PHYSICAL, 20,  15,  90),
	PkmnMove( 36, "Take Down"    , Element::NORMAL  , Type::PHYSICAL, 20,  90,  85),
	PkmnMove( 37, "Thrash"       , Element::NORMAL  , Type::PHYSICAL, 10, 120, 100),
	PkmnMove( 38, "Double Edge"  , Element::NORMAL  , Type::PHYSICAL, 15, 120, 100),
	PkmnMove( 39, "Tail Whip"    , Element::NORMAL  , Type::STATUS  , 30,   0, 100),
	PkmnMove( 40, "Poison Sting ", Element::POISON  , Type::PHYSICAL, 35,  15, 100),
	PkmnMove( 41, "Twineedle"    , Element::BUG     , Type::PHYSICAL, 20,  25, 100),
	PkmnMove( 42, "Pin Missile"  , Element::BUG     , Type::PHYSICAL, 20,  14,  85),
	PkmnMove( 43, "Leer"         , Element::NORMAL  , Type::STATUS  , 30,   0,  85),
	PkmnMove( 44, "Bite"         , Element::NORMAL  , Type::PHYSICAL, 25,  60, 100),
	PkmnMove( 45, "Growl"        , Element::NORMAL  , Type::STATUS  , 40,   0, 100),
	PkmnMove( 46, "Roar"         , Element::NORMAL  , Type::STATUS  , 20,   0, 100),
	PkmnMove( 47, "Sing"         , Element::NORMAL  , Type::STATUS  , 15,   0,  55),
	PkmnMove( 48, "Supersonic"   , Element::NORMAL  , Type::STATUS  , 20,   0,  55),
	PkmnMove( 49, "Sonic Boom"   , Element::NORMAL  , Type::SPECIAL , 20,   0,  90),
	PkmnMove( 50, "Disable"      , Element::NORMAL  , Type::STATUS  , 20,   0, 100),
	PkmnMove( 51, "Acid"         , Element::POISON  , Type::SPECIAL , 30,  40, 100),
	PkmnMove( 52, "Ember"        , Element::FIRE    , Type::SPECIAL , 25,  40, 100),
	PkmnMove( 53, "Flamethrower ", Element::FIRE    , Type::SPECIAL , 15,  95, 100),
	PkmnMove( 54, "Mist"         , Element::ICE     , Type::STATUS  , 30,   0,   0),
	PkmnMove( 55, "Water Gun"    , Element::WATER   , Type::SPECIAL , 25,  40, 100),
	PkmnMove( 56, "Hydro Pump"   , Element::WATER   , Type::SPECIAL ,  5, 120,  80),
	PkmnMove( 57, "Surf"         , Element::WATER   , Type::SPECIAL , 15,  95, 100),
	PkmnMove( 58, "Ice Beam"     , Element::ICE     , Type::SPECIAL , 10,  95, 100),
	PkmnMove( 59, "Blizzard"     , Element::ICE     , Type::SPECIAL ,  5, 120,  70),
	PkmnMove( 60, "Psybeam"      , Element::PSYCHIC , Type::SPECIAL , 20,  65, 100),
	PkmnMove( 61, "Bubble Beam"  , Element::WATER   , Type::SPECIAL , 20,  65, 100),
	PkmnMove( 62, "Aurora Beam"  , Element::ICE     , Type::SPECIAL , 20,  65, 100),
	PkmnMove( 63, "Hyper Beam"   , Element::NORMAL  , Type::SPECIAL ,  5, 150,  90),
	PkmnMove( 64, "Peck"         , Element::FLYING  , Type::PHYSICAL, 35,  35, 100),
	PkmnMove( 65, "Drill Peck"   , Element::FLYING  , Type::PHYSICAL, 20,  80, 100),
	PkmnMove( 66, "Submission"   , Element::FIGHTING, Type::PHYSICAL, 25,  80,  80),
	PkmnMove( 67, "Low Kick"     , Element::FIGHTING, Type::PHYSICAL, 20,   0, 100),
	PkmnMove( 68, "Counter"      , Element::FIGHTING, Type::PHYSICAL, 20,   0, 100),
	PkmnMove( 69, "Seismic Toss ", Element::FIGHTING, Type::PHYSICAL, 20,   0, 100),
	PkmnMove( 70, "Strength"     , Element::NORMAL  , Type::PHYSICAL, 15,  80, 100),
	PkmnMove( 71, "Absorb"       , Element::GRASS   , Type::SPECIAL , 25,  20, 100),
	PkmnMove( 72, "Mega Drain"   , Element::GRASS   , Type::SPECIAL , 15,  40, 100),
	PkmnMove( 73, "Leech Seed"   , Element::GRASS   , Type::STATUS  , 10,   0,  90),
	PkmnMove( 74, "Growth"       , Element::NORMAL  , Type::STATUS  , 40,   0,   0),
	PkmnMove( 75, "Razor Leaf"   , Element::GRASS   , Type::PHYSICAL, 25,  55,  95),
	PkmnMove( 76, "Solar Bram"   , Element::GRASS   , Type::SPECIAL , 10, 120, 100),
	PkmnMove( 77, "Poison Powder", Element::POISON  , Type::STATUS  , 35,   0,  75),
	PkmnMove( 78, "Stun Spore"   , Element::GRASS   , Type::STATUS  , 30,   0,  75),
	PkmnMove( 79, "Sleep Powder ", Element::GRASS   , Type::STATUS  , 15,   0,  75),
	PkmnMove( 80, "Petal Dance"  , Element::GRASS   , Type::SPECIAL , 10, 120, 100),
	PkmnMove( 81, "String Shot"  , Element::BUG     , Type::STATUS  , 40,   0,  95),
	PkmnMove( 82, "Dragon Rage"  , Element::DRAGON  , Type::SPECIAL , 10,   0, 100),
	PkmnMove( 83, "Fire Spin"    , Element::FIRE    , Type::SPECIAL , 15,  35,  85),
	PkmnMove( 84, "Thunder Shock", Element::ELECTRIC, Type::SPECIAL , 30,  40, 100),
	PkmnMove( 85, "Thunderbolt"  , Element::ELECTRIC, Type::SPECIAL , 15,  95, 100),
	PkmnMove( 86, "Thunder Wave ", Element::ELECTRIC, Type::STATUS  , 20,   0, 100),
	PkmnMove( 87, "Thunder"      , Element::ELECTRIC, Type::SPECIAL , 10, 120,  70),
	PkmnMove( 88, "Rock Throw"   , Element::ROCK    , Type::PHYSICAL, 15,  50,  90),
	PkmnMove( 89, "Earthqake"    , Element::GROUND  , Type::PHYSICAL, 10, 100, 100),
	PkmnMove( 90, "Fissure"      , Element::GROUND  , Type::PHYSICAL,  5,   0,   0),
	PkmnMove( 91, "Dig"          , Element::GROUND  , Type::PHYSICAL, 10,  80, 100),
	PkmnMove( 92, "Toxic"        , Element::POISON  , Type::STATUS  , 10,   0,  90),
	PkmnMove( 93, "Confusion"    , Element::PSYCHIC , Type::SPECIAL , 25,  50, 100),
	PkmnMove( 94, "Psychic"      , Element::PSYCHIC , Type::SPECIAL , 10,  90, 100),
	PkmnMove( 95, "Hypnosis"     , Element::PSYCHIC , Type::STATUS  , 20,   0,  60),
	PkmnMove( 96, "Meditate"     , Element::PSYCHIC , Type::STATUS  , 40,   0,   0),
	PkmnMove( 97, "Agility"      , Element::PSYCHIC , Type::STATUS  , 30,   0,   0),
	PkmnMove( 98, "Quick Attack ", Element::NORMAL  , Type::PHYSICAL, 30,  40, 100),
	PkmnMove( 99, "Rage"         , Element::NORMAL  , Type::PHYSICAL, 20,  20, 100),
	PkmnMove(100, "Teleport"     , Element::PSYCHIC , Type::STATUS  , 20,   0,   0),
	PkmnMove(101, "Night Shade"  , Element::GHOST   , Type::SPECIAL , 15,   0, 100),
	PkmnMove(102, "Mimic"        , Element::NORMAL  , Type::STATUS  , 10,   0, 100),
	PkmnMove(103, "Screech"      , Element::NORMAL  , Type::STATUS  , 40,   0,  85),
	PkmnMove(104, "Double Team"  , Element::NORMAL  , Type::STATUS  , 15,   0,   0),
	PkmnMove(105, "Recover"      , Element::NORMAL  , Type::STATUS  , 10,   0,   0),
	PkmnMove(106, "Harden"       , Element::NORMAL  , Type::STATUS  , 30,   0,   0),
	PkmnMove(107, "Minimize"     , Element::NORMAL  , Type::STATUS  , 20,   0,   0),
	PkmnMove(108, "Smoke Screen ", Element::NORMAL  , Type::STATUS  , 20,   0, 100),
	PkmnMove(109, "Confuse Ray"  , Element::GHOST   , Type::STATUS  , 10,   0, 100),
	PkmnMove(110, "Withdraw"     , Element::WATER   , Type::STATUS  , 40,   0,   0),
	PkmnMove(111, "Defense Curl ", Element::NORMAL  , Type::STATUS  , 40,   0,   0),
	PkmnMove(112, "Barrier"      , Element::PSYCHIC , Type::STATUS  , 30,   0,   0),
	PkmnMove(113, "Light Screen ", Element::PSYCHIC , Type::STATUS  , 30,   0,   0),
	PkmnMove(114, "Haze"         , Element::ICE     , Type::STATUS  , 30,   0,   0),
	PkmnMove(115, "Reflect"      , Element::PSYCHIC , Type::STATUS  , 20,   0,   0),
	PkmnMove(116, "Focus Energy ", Element::NORMAL  , Type::STATUS  , 30,   0,   0),
	PkmnMove(117, "Bide"         , Element::NORMAL  , Type::PHYSICAL, 10,   0, 100),
	PkmnMove(118, "Metronome"    , Element::NORMAL  , Type::STATUS  , 10,   0,   0),
	PkmnMove(119, "Mirror Move"  , Element::FLYING  , Type::STATUS  , 20,   0,   0),
	PkmnMove(120, "Selfdestruct ", Element::NORMAL  , Type::PHYSICAL,  5, 200, 100),
	PkmnMove(121, "Egg Bomb"     , Element::NORMAL  , Type::PHYSICAL, 10, 100,  75),
	PkmnMove(122, "Lick"         , Element::GHOST   , Type::PHYSICAL, 30,  20, 100),
	PkmnMove(123, "Smog"         , Element::POISON  , Type::SPECIAL , 20,  20,  70),
	PkmnMove(124, "Sludge"       , Element::POISON  , Type::SPECIAL , 20,  65, 100),
	PkmnMove(125, "Bone Club"    , Element::GROUND  , Type::PHYSICAL, 20,  65,  85),
	PkmnMove(126, "Fire Blast"   , Element::FIRE    , Type::SPECIAL ,  5, 120,  85),
	PkmnMove(127, "Waterfall"    , Element::WATER   , Type::PHYSICAL, 15,  80, 100),
	PkmnMove(128, "Clamp"        , Element::WATER   , Type::PHYSICAL, 10,  35,  85),
	PkmnMove(129, "Swift"        , Element::NORMAL  , Type::SPECIAL , 20,  60,   0),
	PkmnMove(130, "Skull Bash"   , Element::NORMAL  , Type::PHYSICAL, 15, 100, 100),
	PkmnMove(131, "Spike Cannon ", Element::NORMAL  , Type::PHYSICAL, 15,  20, 100),
	PkmnMove(132, "Constrict"    , Element::NORMAL  , Type::PHYSICAL, 35,  10, 100),
	PkmnMove(133, "Amnesia"      , Element::PSYCHIC , Type::STATUS  , 20,   0,   0),
	PkmnMove(134, "Kinesis"      , Element::PSYCHIC , Type::STATUS  , 15,   0,  80),
	PkmnMove(135, "Softboiled"   , Element::NORMAL  , Type::STATUS  , 10,   0,   0),
	PkmnMove(136, "Hi Jump Kick ", Element::FIGHTING, Type::PHYSICAL, 10, 130,  90),
	PkmnMove(137, "Glare"        , Element::NORMAL  , Type::STATUS  , 30,   0,  90),
	PkmnMove(138, "Dream Eater"  , Element::PSYCHIC , Type::SPECIAL , 15, 100, 100),
	PkmnMove(139, "Poison Gas"   , Element::POISON  , Type::STATUS  , 40,   0,  85),
	PkmnMove(140, "Barrage"      , Element::NORMAL  , Type::PHYSICAL, 20,  15,  85),
	PkmnMove(141, "Leech Life"   , Element::BUG     , Type::PHYSICAL, 15,  20, 100),
	PkmnMove(142, "Lovely Kiss"  , Element::NORMAL  , Type::STATUS  , 10,   0,  75),
	PkmnMove(143, "Sky Attack"   , Element::FLYING  , Type::PHYSICAL,  5, 140,  90),
	PkmnMove(144, "Transform"    , Element::NORMAL  , Type::STATUS  , 10,   0,   0),
	PkmnMove(145, "Bubble"       , Element::WATER   , Type::SPECIAL , 30,  20, 100),
	PkmnMove(146, "Dizzy Punch"  , Element::NORMAL  , Type::PHYSICAL, 10,  70, 100),
	PkmnMove(147, "Spore"        , Element::GRASS   , Type::STATUS  , 15,   0, 100),
	PkmnMove(148, "Flash"        , Element::NORMAL  , Type::STATUS  , 20,   0, 100),
	PkmnMove(149, "Psywave"      , Element::PSYCHIC , Type::SPECIAL , 15,   0,  80),
	PkmnMove(150, "Splash"       , Element::NORMAL  , Type::STATUS  , 40,   0,   0),
	PkmnMove(151, "Acid Armor"   , Element::POISON  , Type::STATUS  , 40,   0,   0),
	PkmnMove(152, "Crabhammer"   , Element::WATER   , Type::PHYSICAL, 10,  90,  90),
	PkmnMove(153, "Explosion"    , Element::NORMAL  , Type::PHYSICAL,  5, 250, 100),
	PkmnMove(154, "Fury Swipes"  , Element::NORMAL  , Type::PHYSICAL, 15,  18,  80),
	PkmnMove(155, "Bonemerang"   , Element::GROUND  , Type::PHYSICAL, 10,  50,  90),
	PkmnMove(156, "Rest"         , Element::PSYCHIC , Type::STATUS  , 10,   0,   0),
	PkmnMove(157, "Rock Slide"   , Element::ROCK    , Type::PHYSICAL, 10,  75,  90),
	PkmnMove(158, "Hyper Fang"   , Element::NORMAL  , Type::PHYSICAL, 15,  80,  90),
	PkmnMove(159, "Sharpen"      , Element::NORMAL  , Type::STATUS  , 30,   0,   0),
	PkmnMove(160, "Conversion"   , Element::NORMAL  , Type::STATUS  , 30,   0,   0),
	PkmnMove(161, "Tri Attack"   , Element::NORMAL  , Type::SPECIAL , 10,  80, 100),
	PkmnMove(162, "Super Fang"   , Element::NORMAL  , Type::PHYSICAL, 10,   0,  90),
	PkmnMove(163, "Slash"        , Element::NORMAL  , Type::PHYSICAL, 20,  70, 100),
	PkmnMove(164, "Substitute"   , Element::NORMAL  , Type::STATUS  , 10,   0,   0),
	PkmnMove(165, "Struggle"     , Element::NORMAL  , Type::PHYSICAL,  1,  50, 100)};

