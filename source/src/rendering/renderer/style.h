#ifndef STYLE_H
#define STYLE_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct Style
	{
		vec4  color;
		float strokeWidth;
	};

	namespace Colors
	{
		extern const glm::vec4 cloudyBlue;
		extern const glm::vec4 darkPastelGreen;
		extern const glm::vec4 dust;
		extern const glm::vec4 electricLime;
		extern const glm::vec4 freshGreen;
		extern const glm::vec4 lightEggplant;
		extern const glm::vec4 nastyGreen;
		extern const glm::vec4 reallyLightBlue;
		extern const glm::vec4 tea;
		extern const glm::vec4 warmPurple;
		extern const glm::vec4 yellowishTan;
		extern const glm::vec4 cement;
		extern const glm::vec4 darkGrassGreen;
		extern const glm::vec4 dustyTeal;
		extern const glm::vec4 greyTeal;
		extern const glm::vec4 macaroniAndCheese;
		extern const glm::vec4 pinkishTan;
		extern const glm::vec4 spruce;
		extern const glm::vec4 strongBlue;
		extern const glm::vec4 toxicGreen;
		extern const glm::vec4 windowsBlue;
		extern const glm::vec4 blueBlue;
		extern const glm::vec4 blueWithAHintOfPurple;
		extern const glm::vec4 booger;
		extern const glm::vec4 brightSeaGreen;
		extern const glm::vec4 darkGreenBlue;
		extern const glm::vec4 deepTurquoise;
		extern const glm::vec4 greenTeal;
		extern const glm::vec4 strongPink;
		extern const glm::vec4 bland;
		extern const glm::vec4 deepAqua;
		extern const glm::vec4 lavenderPink;
		extern const glm::vec4 lightMossGreen;
		extern const glm::vec4 lightSeafoamGreen;
		extern const glm::vec4 oliveYellow;
		extern const glm::vec4 pigPink;
		extern const glm::vec4 deepLilac;
		extern const glm::vec4 desert;
		extern const glm::vec4 dustyLavender;
		extern const glm::vec4 purpleyGrey;
		extern const glm::vec4 purply;
		extern const glm::vec4 candyPink;
		extern const glm::vec4 lightPastelGreen;
		extern const glm::vec4 boringGreen;
		extern const glm::vec4 kiwiGreen;
		extern const glm::vec4 lightGreyGreen;
		extern const glm::vec4 orangePink;
		extern const glm::vec4 teaGreen;
		extern const glm::vec4 veryLightBrown;
		extern const glm::vec4 eggShell;
		extern const glm::vec4 eggplantPurple;
		extern const glm::vec4 powderPink;
		extern const glm::vec4 reddishGrey;
		extern const glm::vec4 babyShitBrown;
		extern const glm::vec4 liliac;
		extern const glm::vec4 stormyBlue;
		extern const glm::vec4 uglyBrown;
		extern const glm::vec4 custard;
		extern const glm::vec4 darkishPink;
		extern const glm::vec4 deepBrown;
		extern const glm::vec4 greenishBeige;
		extern const glm::vec4 manilla;
		extern const glm::vec4 offBlue;
		extern const glm::vec4 battleshipGrey;
		extern const glm::vec4 brownyGreen;
		extern const glm::vec4 bruise;
		extern const glm::vec4 kelleyGreen;
		extern const glm::vec4 sicklyYellow;
		extern const glm::vec4 sunnyYellow;
		extern const glm::vec4 azul;
		extern const glm::vec4 darkGreen;
		extern const glm::vec4 greenYellow;
		extern const glm::vec4 lichen;
		extern const glm::vec4 lightLightGreen;
		extern const glm::vec4 paleGold;
		extern const glm::vec4 sunYellow;
		extern const glm::vec4 tanGreen;
		extern const glm::vec4 burple;
		extern const glm::vec4 butterscotch;
		extern const glm::vec4 toupe;
		extern const glm::vec4 darkCream;
		extern const glm::vec4 indianRed;
		extern const glm::vec4 lightLavendar;
		extern const glm::vec4 poisonGreen;
		extern const glm::vec4 babyPukeGreen;
		extern const glm::vec4 brightYellowGreen;
		extern const glm::vec4 charcoalGrey;
		extern const glm::vec4 squash;
		extern const glm::vec4 cinnamon;
		extern const glm::vec4 lightPeaGreen;
		extern const glm::vec4 radioactiveGreen;
		extern const glm::vec4 rawSienna;
		extern const glm::vec4 babyPurple;
		extern const glm::vec4 cocoa;
		extern const glm::vec4 lightRoyalBlue;
		extern const glm::vec4 orangeish;
		extern const glm::vec4 rustBrown;
		extern const glm::vec4 sandBrown;
		extern const glm::vec4 swamp;
		extern const glm::vec4 tealishGreen;
		extern const glm::vec4 burntSiena;
		extern const glm::vec4 camo;
		extern const glm::vec4 duskBlue;
		extern const glm::vec4 fern;
		extern const glm::vec4 oldRose;
		extern const glm::vec4 paleLightGreen;
		extern const glm::vec4 peachyPink;
		extern const glm::vec4 rosyPink;
		extern const glm::vec4 lightBluishGreen;
		extern const glm::vec4 lightBrightGreen;
		extern const glm::vec4 lightNeonGreen;
		extern const glm::vec4 lightSeafoam;
		extern const glm::vec4 tiffanyBlue;
		extern const glm::vec4 washedOutGreen;
		extern const glm::vec4 brownyOrange;
		extern const glm::vec4 nIceBlue;
		extern const glm::vec4 sapphire;
		extern const glm::vec4 greyishTeal;
		extern const glm::vec4 orangeyYellow;
		extern const glm::vec4 parchment;
		extern const glm::vec4 straw;
		extern const glm::vec4 veryDarkBrown;
		extern const glm::vec4 terracota;
		extern const glm::vec4 uglyBlue;
		extern const glm::vec4 clearBlue;
		extern const glm::vec4 creme;
		extern const glm::vec4 foamGreen;
		extern const glm::vec4 greyGreen;
		extern const glm::vec4 lightGold;
		extern const glm::vec4 seafoamBlue;
		extern const glm::vec4 topaz;
		extern const glm::vec4 violetPink;
		extern const glm::vec4 winterGreen;
		extern const glm::vec4 yellowTan;
		extern const glm::vec4 darkFuchsia;
		extern const glm::vec4 indigoBlue;
		extern const glm::vec4 lightYellowishGreen;
		extern const glm::vec4 paleMagenta;
		extern const glm::vec4 richPurple;
		extern const glm::vec4 sunflowerYellow;
		extern const glm::vec4 greenBlue;
		extern const glm::vec4 leather;
		extern const glm::vec4 racingGreen;
		extern const glm::vec4 vividPurple;
		extern const glm::vec4 darkRoyalBlue;
		extern const glm::vec4 hazel;
		extern const glm::vec4 mutedPink;
		extern const glm::vec4 boogerGreen;
		extern const glm::vec4 canary;
		extern const glm::vec4 coolGrey;
		extern const glm::vec4 darkTaupe;
		extern const glm::vec4 darkishPurple;
		extern const glm::vec4 trueGreen;
		extern const glm::vec4 coralPink;
		extern const glm::vec4 darkSage;
		extern const glm::vec4 darkSlateBlue;
		extern const glm::vec4 flatBlue;
		extern const glm::vec4 mushroom;
		extern const glm::vec4 richBlue;
		extern const glm::vec4 dirtyPurple;
		extern const glm::vec4 greenBlue_;
		extern const glm::vec4 ickyGreen;
		extern const glm::vec4 lightKhaki;
		extern const glm::vec4 warmBlue;
		extern const glm::vec4 darkHotPink;
		extern const glm::vec4 deepSeaBlue;
		extern const glm::vec4 carmine;
		extern const glm::vec4 darkYellowGreen;
		extern const glm::vec4 palePeach;
		extern const glm::vec4 plumPurple;
		extern const glm::vec4 goldenRod;
		extern const glm::vec4 neonRed;
		extern const glm::vec4 oldPink;
		extern const glm::vec4 veryPaleBlue;
		extern const glm::vec4 bloodOrange;
		extern const glm::vec4 grapefruit;
		extern const glm::vec4 sandYellow;
		extern const glm::vec4 clayBrown;
		extern const glm::vec4 darkBlueGrey;
		extern const glm::vec4 flatGreen;
		extern const glm::vec4 lightGreenBlue;
		extern const glm::vec4 warmPink;
		extern const glm::vec4 dodgerBlue;
		extern const glm::vec4 grossGreen;
		extern const glm::vec4 ice;
		extern const glm::vec4 metallicBlue;
		extern const glm::vec4 paleSalmon;
		extern const glm::vec4 sapGreen;
		extern const glm::vec4 algae;
		extern const glm::vec4 blueyGrey;
		extern const glm::vec4 greenyGrey;
		extern const glm::vec4 highLighterGreen;
		extern const glm::vec4 lightLightBlue;
		extern const glm::vec4 lightMint;
		extern const glm::vec4 rawUmber;
		extern const glm::vec4 vividBlue;
		extern const glm::vec4 deepLavender;
		extern const glm::vec4 dullTeal;
		extern const glm::vec4 lightGreenishBlue;
		extern const glm::vec4 mudGreen;
		extern const glm::vec4 pinky;
		extern const glm::vec4 redWine;
		extern const glm::vec4 shitGreen;
		extern const glm::vec4 tanBrown;
		extern const glm::vec4 darkBlue;
		extern const glm::vec4 rosa;
		extern const glm::vec4 lipstick;
		extern const glm::vec4 paleMauve;
		extern const glm::vec4 claret;
		extern const glm::vec4 dandelion;
		extern const glm::vec4 orangeRed;
		extern const glm::vec4 poopGreen;
		extern const glm::vec4 ruby;
		extern const glm::vec4 dark;
		extern const glm::vec4 greenishTurquoise;
		extern const glm::vec4 pastelRed;
		extern const glm::vec4 pissYellow;
		extern const glm::vec4 brightCyan;
		extern const glm::vec4 darkCoral;
		extern const glm::vec4 algaeGreen;
		extern const glm::vec4 darkishRed;
		extern const glm::vec4 reddyBrown;
		extern const glm::vec4 blushPink;
		extern const glm::vec4 camouflageGreen;
		extern const glm::vec4 lawnGreen;
		extern const glm::vec4 putty;
		extern const glm::vec4 vibrantBlue;
		extern const glm::vec4 darkSand;
		extern const glm::vec4 purpleBlue;
		extern const glm::vec4 saffron;
		extern const glm::vec4 twiLight;
		extern const glm::vec4 warmBrown;
		extern const glm::vec4 blueGrey;
		extern const glm::vec4 bubbleGumPink;
		extern const glm::vec4 duckEggBlue;
		extern const glm::vec4 greenishCyan;
		extern const glm::vec4 petrol;
		extern const glm::vec4 royal;
		extern const glm::vec4 butter;
		extern const glm::vec4 dustyOrange;
		extern const glm::vec4 offYellow;
		extern const glm::vec4 paleOliveGreen;
		extern const glm::vec4 orangish;
		extern const glm::vec4 leaf;
		extern const glm::vec4 lightBlueGrey;
		extern const glm::vec4 driedBlood;
		extern const glm::vec4 lightishPurple;
		extern const glm::vec4 rustyRed;
		extern const glm::vec4 lavenderBlue;
		extern const glm::vec4 lightGrassGreen;
		extern const glm::vec4 lightMintGreen;
		extern const glm::vec4 sunflower;
		extern const glm::vec4 velvet;
		extern const glm::vec4 brickOrange;
		extern const glm::vec4 lightishRed;
		extern const glm::vec4 pureBlue;
		extern const glm::vec4 twiLightBlue;
		extern const glm::vec4 violetRed;
		extern const glm::vec4 yellowyBrown;
		extern const glm::vec4 carnation;
		extern const glm::vec4 muddyYellow;
		extern const glm::vec4 darkSeafoamGreen;
		extern const glm::vec4 deepRose;
		extern const glm::vec4 dustyRed;
		extern const glm::vec4 greyBlue;
		extern const glm::vec4 lemonLime;
		extern const glm::vec4 purplePink;
		extern const glm::vec4 brownYellow;
		extern const glm::vec4 purpleBrown;
		extern const glm::vec4 wisteria;
		extern const glm::vec4 bananaYellow;
		extern const glm::vec4 lipstickRed;
		extern const glm::vec4 waterBlue;
		extern const glm::vec4 brownGrey;
		extern const glm::vec4 vibrantPurple;
		extern const glm::vec4 babyGreen;
		extern const glm::vec4 barfGreen;
		extern const glm::vec4 eggshellBlue;
		extern const glm::vec4 sandyYellow;
		extern const glm::vec4 coolGreen;
		extern const glm::vec4 pale;
		extern const glm::vec4 blueGrey_;
		extern const glm::vec4 hotMagenta;
		extern const glm::vec4 greyBlue_;
		extern const glm::vec4 purpley;
		extern const glm::vec4 babyShitGreen;
		extern const glm::vec4 brownishPink;
		extern const glm::vec4 darkAquaMarine;
		extern const glm::vec4 diarrhea;
		extern const glm::vec4 lightMustard;
		extern const glm::vec4 paleSkyBlue;
		extern const glm::vec4 turtleGreen;
		extern const glm::vec4 brightOlive;
		extern const glm::vec4 darkGreyBlue;
		extern const glm::vec4 greenyBrown;
		extern const glm::vec4 lemonGreen;
		extern const glm::vec4 lightPeriwinkle;
		extern const glm::vec4 seaweedGreen;
		extern const glm::vec4 sunshineYellow;
		extern const glm::vec4 uglyPurple;
		extern const glm::vec4 mediumPink;
		extern const glm::vec4 pukeBrown;
		extern const glm::vec4 veryLightPink;
		extern const glm::vec4 viridian;
		extern const glm::vec4 bile;
		extern const glm::vec4 fadedYellow;
		extern const glm::vec4 veryPaleGreen;
		extern const glm::vec4 vibrantGreen;
		extern const glm::vec4 brightLime;
		extern const glm::vec4 sPearMint;
		extern const glm::vec4 lightAquaMarine;
		extern const glm::vec4 lightSage;
		extern const glm::vec4 yellowGreen;
		extern const glm::vec4 babyPoo;
		extern const glm::vec4 darkSeafoam;
		extern const glm::vec4 deepTeal;
		extern const glm::vec4 heather;
		extern const glm::vec4 rustOrange;
		extern const glm::vec4 dirtyBlue;
		extern const glm::vec4 fernGreen;
		extern const glm::vec4 brightLilac;
		extern const glm::vec4 weirdGreen;
		extern const glm::vec4 peacockBlue;
		extern const glm::vec4 avocadoGreen;
		extern const glm::vec4 fadedOrange;
		extern const glm::vec4 grapePurple;
		extern const glm::vec4 hotGreen;
		extern const glm::vec4 limeYellow;
		extern const glm::vec4 mango;
		extern const glm::vec4 shamrock;
		extern const glm::vec4 bubblegum;
		extern const glm::vec4 purplishBrown;
		extern const glm::vec4 vomitYellow;
		extern const glm::vec4 paleCyan;
		extern const glm::vec4 keyLime;
		extern const glm::vec4 tomatoRed;
		extern const glm::vec4 lightGreen;
		extern const glm::vec4 merlot;
		extern const glm::vec4 nightBlue;
		extern const glm::vec4 purpleishPink;
		extern const glm::vec4 apple;
		extern const glm::vec4 babyPoopGreen;
		extern const glm::vec4 greenApple;
		extern const glm::vec4 heliotrope;
		extern const glm::vec4 yellowGreen_;
		extern const glm::vec4 almostBlack;
		extern const glm::vec4 coolBlue;
		extern const glm::vec4 leafyGreen;
		extern const glm::vec4 mustardBrown;
		extern const glm::vec4 dusk;
		extern const glm::vec4 dullBrown;
		extern const glm::vec4 frogGreen;
		extern const glm::vec4 vividGreen;
		extern const glm::vec4 brightLightGreen;
		extern const glm::vec4 fluroGreen;
		extern const glm::vec4 kiwi;
		extern const glm::vec4 seaweed;
		extern const glm::vec4 navyGreen;
		extern const glm::vec4 ultraMarineBlue;
		extern const glm::vec4 iris;
		extern const glm::vec4 pastelOrange;
		extern const glm::vec4 yellowishOrange;
		extern const glm::vec4 perrywinkle;
		extern const glm::vec4 tealish;
		extern const glm::vec4 darkPlum;
		extern const glm::vec4 pear;
		extern const glm::vec4 pinkishOrange;
		extern const glm::vec4 midnightPurple;
		extern const glm::vec4 lightUrple;
		extern const glm::vec4 darkMint;
		extern const glm::vec4 greenishTan;
		extern const glm::vec4 lightBurgundy;
		extern const glm::vec4 turquoiseBlue;
		extern const glm::vec4 uglyPink;
		extern const glm::vec4 sandy;
		extern const glm::vec4 electricPink;
		extern const glm::vec4 mutedPurple;
		extern const glm::vec4 midGreen;
		extern const glm::vec4 greyish;
		extern const glm::vec4 neonYellow;
		extern const glm::vec4 banana;
		extern const glm::vec4 carnationPink;
		extern const glm::vec4 tomato;
		extern const glm::vec4 sea;
		extern const glm::vec4 muddyBrown;
		extern const glm::vec4 turquoiseGreen;
		extern const glm::vec4 buff;
		extern const glm::vec4 fawn;
		extern const glm::vec4 mutedBlue;
		extern const glm::vec4 paleRose;
		extern const glm::vec4 darkMintGreen;
		extern const glm::vec4 amethyst;
		extern const glm::vec4 blueGreen;
		extern const glm::vec4 chestnut;
		extern const glm::vec4 sickGreen;
		extern const glm::vec4 pea;
		extern const glm::vec4 rustyOrange;
		extern const glm::vec4 stone;
		extern const glm::vec4 roseRed;
		extern const glm::vec4 paleAqua;
		extern const glm::vec4 deepOrange;
		extern const glm::vec4 earth;
		extern const glm::vec4 mossyGreen;
		extern const glm::vec4 grassyGreen;
		extern const glm::vec4 paleLimeGreen;
		extern const glm::vec4 lightGreyBlue;
		extern const glm::vec4 paleGrey;
		extern const glm::vec4 asparagus;
		extern const glm::vec4 blueBerry;
		extern const glm::vec4 purpleRed;
		extern const glm::vec4 paleLime;
		extern const glm::vec4 greenishTeal;
		extern const glm::vec4 caramel;
		extern const glm::vec4 deepMagenta;
		extern const glm::vec4 lightPeach;
		extern const glm::vec4 milkChocolate;
		extern const glm::vec4 ocher;
		extern const glm::vec4 offGreen;
		extern const glm::vec4 purplyPink;
		extern const glm::vec4 lightBlue;
		extern const glm::vec4 duSkyBlue;
		extern const glm::vec4 golden;
		extern const glm::vec4 lightBeige;
		extern const glm::vec4 butterYellow;
		extern const glm::vec4 duSkyPurple;
		extern const glm::vec4 frenchBlue;
		extern const glm::vec4 uglyYellow;
		extern const glm::vec4 greenyYellow;
		extern const glm::vec4 orangishRed;
		extern const glm::vec4 shamrockGreen;
		extern const glm::vec4 orangishBrown;
		extern const glm::vec4 treeGreen;
		extern const glm::vec4 deepViolet;
		extern const glm::vec4 gunmetal;
		extern const glm::vec4 bluePurple;
		extern const glm::vec4 cherry;
		extern const glm::vec4 sandyBrown;
		extern const glm::vec4 warmGrey;
		extern const glm::vec4 darkIndigo;
		extern const glm::vec4 midnight;
		extern const glm::vec4 blueyGreen;
		extern const glm::vec4 greyPink;
		extern const glm::vec4 softPurple;
		extern const glm::vec4 blood;
		extern const glm::vec4 brownRed;
		extern const glm::vec4 mediumGrey;
		extern const glm::vec4 berry;
		extern const glm::vec4 poo;
		extern const glm::vec4 purpleyPink;
		extern const glm::vec4 lightSalmon;
		extern const glm::vec4 snot;
		extern const glm::vec4 easterPurple;
		extern const glm::vec4 lightYellowGreen;
		extern const glm::vec4 darkNavyBlue;
		extern const glm::vec4 drab;
		extern const glm::vec4 lightRose;
		extern const glm::vec4 rouge;
		extern const glm::vec4 purplishRed;
		extern const glm::vec4 sLimeGreen;
		extern const glm::vec4 babyPoop;
		extern const glm::vec4 irishGreen;
		extern const glm::vec4 pinkPurple;
		extern const glm::vec4 darkNavy;
		extern const glm::vec4 greenyBlue;
		extern const glm::vec4 lightPlum;
		extern const glm::vec4 pinkishGrey;
		extern const glm::vec4 dirtyOrange;
		extern const glm::vec4 rustRed;
		extern const glm::vec4 paleLilac;
		extern const glm::vec4 orangeyRed;
		extern const glm::vec4 primaryBlue;
		extern const glm::vec4 kermitGreen;
		extern const glm::vec4 brownishPurple;
		extern const glm::vec4 murkyGreen;
		extern const glm::vec4 wheat;
		extern const glm::vec4 veryDarkPurple;
		extern const glm::vec4 bottleGreen;
		extern const glm::vec4 waterMelon;
		extern const glm::vec4 deepSkyBlue;
		extern const glm::vec4 fireEngineRed;
		extern const glm::vec4 yellowOchre;
		extern const glm::vec4 pumpkinOrange;
		extern const glm::vec4 paleOlive;
		extern const glm::vec4 lightLilac;
		extern const glm::vec4 lightishGreen;
		extern const glm::vec4 carolinaBlue;
		extern const glm::vec4 mulBerry;
		extern const glm::vec4 shockingPink;
		extern const glm::vec4 auburn;
		extern const glm::vec4 brightLimeGreen;
		extern const glm::vec4 celadon;
		extern const glm::vec4 pinkishBrown;
		extern const glm::vec4 pooBrown;
		extern const glm::vec4 brightSkyBlue;
		extern const glm::vec4 celery;
		extern const glm::vec4 dirtBrown;
		extern const glm::vec4 strawBerry;
		extern const glm::vec4 darkLime;
		extern const glm::vec4 copper;
		extern const glm::vec4 mediumBrown;
		extern const glm::vec4 mutedGreen;
		extern const glm::vec4 robinsEgg;
		extern const glm::vec4 brightAqua;
		extern const glm::vec4 brightLavender;
		extern const glm::vec4 ivory;
		extern const glm::vec4 veryLightPurple;
		extern const glm::vec4 lightNavy;
		extern const glm::vec4 pinkRed;
		extern const glm::vec4 oliveBrown;
		extern const glm::vec4 poopBrown;
		extern const glm::vec4 mustardGreen;
		extern const glm::vec4 oceanGreen;
		extern const glm::vec4 veryDarkBlue;
		extern const glm::vec4 dustyGreen;
		extern const glm::vec4 lightNavyBlue;
		extern const glm::vec4 mintyGreen;
		extern const glm::vec4 adobe;
		extern const glm::vec4 barney;
		extern const glm::vec4 jadeGreen;
		extern const glm::vec4 brightLightBlue;
		extern const glm::vec4 lightLime;
		extern const glm::vec4 darkKhaki;
		extern const glm::vec4 orangeYellow;
		extern const glm::vec4 ocre;
		extern const glm::vec4 maize;
		extern const glm::vec4 fadedPink;
		extern const glm::vec4 britishRacingGreen;
		extern const glm::vec4 sandStone;
		extern const glm::vec4 mudBrown;
		extern const glm::vec4 lightSeaGreen;
		extern const glm::vec4 robinEggBlue;
		extern const glm::vec4 aquaMarine;
		extern const glm::vec4 darkSeaGreen;
		extern const glm::vec4 softPink;
		extern const glm::vec4 orangeyBrown;
		extern const glm::vec4 cherryRed;
		extern const glm::vec4 burntYellow;
		extern const glm::vec4 brownishGrey;
		extern const glm::vec4 camel;
		extern const glm::vec4 purplishGrey;
		extern const glm::vec4 marine;
		extern const glm::vec4 greyishPink;
		extern const glm::vec4 paleTurquoise;
		extern const glm::vec4 pastelYellow;
		extern const glm::vec4 blueyPurple;
		extern const glm::vec4 canaryYellow;
		extern const glm::vec4 fadedRed;
		extern const glm::vec4 sepia;
		extern const glm::vec4 coffee;
		extern const glm::vec4 brightMagenta;
		extern const glm::vec4 mocha;
		extern const glm::vec4 ecru;
		extern const glm::vec4 purpleish;
		extern const glm::vec4 cranBerry;
		extern const glm::vec4 darkishGreen;
		extern const glm::vec4 brownOrange;
		extern const glm::vec4 duSkyRose;
		extern const glm::vec4 melon;
		extern const glm::vec4 sicklyGreen;
		extern const glm::vec4 silver;
		extern const glm::vec4 purplyBlue;
		extern const glm::vec4 purpleishBlue;
		extern const glm::vec4 hospitalGreen;
		extern const glm::vec4 shitBrown;
		extern const glm::vec4 midBlue;
		extern const glm::vec4 amber;
		extern const glm::vec4 easterGreen;
		extern const glm::vec4 softBlue;
		extern const glm::vec4 ceruleanBlue;
		extern const glm::vec4 goldenBrown;
		extern const glm::vec4 brightTurquoise;
		extern const glm::vec4 redPink;
		extern const glm::vec4 redPurple;
		extern const glm::vec4 greyishBrown;
		extern const glm::vec4 vermillion;
		extern const glm::vec4 russet;
		extern const glm::vec4 steelGrey;
		extern const glm::vec4 lighterPurple;
		extern const glm::vec4 brightViolet;
		extern const glm::vec4 prussianBlue;
		extern const glm::vec4 slateGreen;
		extern const glm::vec4 dirtyPink;
		extern const glm::vec4 darkBlueGreen;
		extern const glm::vec4 pine;
		extern const glm::vec4 yellowyGreen;
		extern const glm::vec4 darkGold;
		extern const glm::vec4 bluish;
		extern const glm::vec4 darkishBlue;
		extern const glm::vec4 dullRed;
		extern const glm::vec4 pinkyRed;
		extern const glm::vec4 bronze;
		extern const glm::vec4 paleTeal;
		extern const glm::vec4 militaryGreen;
		extern const glm::vec4 barbiePink;
		extern const glm::vec4 bubblegumPink;
		extern const glm::vec4 peaSoupGreen;
		extern const glm::vec4 darkMustard;
		extern const glm::vec4 shit;
		extern const glm::vec4 mediumPurple;
		extern const glm::vec4 veryDarkGreen;
		extern const glm::vec4 dirt;
		extern const glm::vec4 duSkyPink;
		extern const glm::vec4 redViolet;
		extern const glm::vec4 lemonYellow;
		extern const glm::vec4 pistachio;
		extern const glm::vec4 dullYellow;
		extern const glm::vec4 darkLimeGreen;
		extern const glm::vec4 denimBlue;
		extern const glm::vec4 tealBlue;
		extern const glm::vec4 lightishBlue;
		extern const glm::vec4 purpleyBlue;
		extern const glm::vec4 lightIndigo;
		extern const glm::vec4 swampGreen;
		extern const glm::vec4 brownGreen;
		extern const glm::vec4 darkMaroon;
		extern const glm::vec4 hotPurple;
		extern const glm::vec4 darkForestGreen;
		extern const glm::vec4 fadedBlue;
		extern const glm::vec4 drabGreen;
		extern const glm::vec4 lightLimeGreen;
		extern const glm::vec4 snotGreen;
		extern const glm::vec4 yellowish;
		extern const glm::vec4 lightBlueGreen;
		extern const glm::vec4 bordeaux;
		extern const glm::vec4 lightMauve;
		extern const glm::vec4 ocean;
		extern const glm::vec4 mariGold;
		extern const glm::vec4 muddyGreen;
		extern const glm::vec4 dullOrange;
		extern const glm::vec4 steel;
		extern const glm::vec4 electricPurple;
		extern const glm::vec4 fluorescentGreen;
		extern const glm::vec4 yellowishBrown;
		extern const glm::vec4 blush;
		extern const glm::vec4 softGreen;
		extern const glm::vec4 brightOrange;
		extern const glm::vec4 lemon;
		extern const glm::vec4 purpleGrey;
		extern const glm::vec4 acidGreen;
		extern const glm::vec4 paleLavender;
		extern const glm::vec4 violetBlue;
		extern const glm::vec4 lightForestGreen;
		extern const glm::vec4 burntRed;
		extern const glm::vec4 khakiGreen;
		extern const glm::vec4 cerise;
		extern const glm::vec4 fadedPurple;
		extern const glm::vec4 apricot;
		extern const glm::vec4 darkOliveGreen;
		extern const glm::vec4 greyBrown;
		extern const glm::vec4 greenGrey;
		extern const glm::vec4 trueBlue;
		extern const glm::vec4 paleViolet;
		extern const glm::vec4 periwinkleBlue;
		extern const glm::vec4 lightSkyBlue;
		extern const glm::vec4 blurple;
		extern const glm::vec4 greenBrown;
		extern const glm::vec4 blueGreen_;
		extern const glm::vec4 brightTeal;
		extern const glm::vec4 brownishYellow;
		extern const glm::vec4 peaSoup;
		extern const glm::vec4 forest;
		extern const glm::vec4 barneyPurple;
		extern const glm::vec4 ultraMarine;
		extern const glm::vec4 purplish;
		extern const glm::vec4 pukeYellow;
		extern const glm::vec4 bluishGrey;
		extern const glm::vec4 darkPeriwinkle;
		extern const glm::vec4 darkLilac;
		extern const glm::vec4 reddish;
		extern const glm::vec4 lightMaroon;
		extern const glm::vec4 dustyPurple;
		extern const glm::vec4 terraCotta;
		extern const glm::vec4 avocado;
		extern const glm::vec4 marineBlue;
		extern const glm::vec4 tealGreen;
		extern const glm::vec4 slateGrey;
		extern const glm::vec4 lighterGreen;
		extern const glm::vec4 electricGreen;
		extern const glm::vec4 dustyBlue;
		extern const glm::vec4 goldenYellow;
		extern const glm::vec4 brightYellow;
		extern const glm::vec4 lightLavender;
		extern const glm::vec4 umber;
		extern const glm::vec4 poop;
		extern const glm::vec4 darkPeach;
		extern const glm::vec4 jungleGreen;
		extern const glm::vec4 eggshell;
		extern const glm::vec4 denim;
		extern const glm::vec4 yellowBrown;
		extern const glm::vec4 dullPurple;
		extern const glm::vec4 chocolateBrown;
		extern const glm::vec4 wineRed;
		extern const glm::vec4 neonBlue;
		extern const glm::vec4 dirtyGreen;
		extern const glm::vec4 lightTan;
		extern const glm::vec4 iceBlue;
		extern const glm::vec4 cadetBlue;
		extern const glm::vec4 darkMauve;
		extern const glm::vec4 veryLightBlue;
		extern const glm::vec4 greyPurple;
		extern const glm::vec4 pastelPink;
		extern const glm::vec4 veryLightGreen;
		extern const glm::vec4 darkSkyBlue;
		extern const glm::vec4 everGreen;
		extern const glm::vec4 dullPink;
		extern const glm::vec4 aubergine;
		extern const glm::vec4 mahogany;
		extern const glm::vec4 reddishOrange;
		extern const glm::vec4 deepGreen;
		extern const glm::vec4 vomitGreen;
		extern const glm::vec4 purplePink_;
		extern const glm::vec4 dustyPink;
		extern const glm::vec4 fadedGreen;
		extern const glm::vec4 camoGreen;
		extern const glm::vec4 pinkyPurple;
		extern const glm::vec4 pinkPurple_;
		extern const glm::vec4 brownishRed;
		extern const glm::vec4 darkRose;
		extern const glm::vec4 mud;
		extern const glm::vec4 brownish;
		extern const glm::vec4 emeraldGreen;
		extern const glm::vec4 paleBrown;
		extern const glm::vec4 dullBlue;
		extern const glm::vec4 burntUmber;
		extern const glm::vec4 mediumGreen;
		extern const glm::vec4 clay;
		extern const glm::vec4 lightAqua;
		extern const glm::vec4 lightOliveGreen;
		extern const glm::vec4 brownishOrange;
		extern const glm::vec4 darkAqua;
		extern const glm::vec4 purplishPink;
		extern const glm::vec4 darkSalmon;
		extern const glm::vec4 greenishGrey;
		extern const glm::vec4 jade;
		extern const glm::vec4 uglyGreen;
		extern const glm::vec4 darkBeige;
		extern const glm::vec4 emerald;
		extern const glm::vec4 paleRed;
		extern const glm::vec4 lightMagenta;
		extern const glm::vec4 sky;
		extern const glm::vec4 lightCyan;
		extern const glm::vec4 yellowOrange;
		extern const glm::vec4 reddishPurple;
		extern const glm::vec4 reddishPink;
		extern const glm::vec4 orchid;
		extern const glm::vec4 dirtyYellow;
		extern const glm::vec4 orangeRed_;
		extern const glm::vec4 deepRed;
		extern const glm::vec4 orangeBrown;
		extern const glm::vec4 cobaltBlue;
		extern const glm::vec4 neonPink;
		extern const glm::vec4 rosePink;
		extern const glm::vec4 greyishPurple;
		extern const glm::vec4 raspBerry;
		extern const glm::vec4 aquaGreen;
		extern const glm::vec4 salmonPink;
		extern const glm::vec4 tangerine;
		extern const glm::vec4 brownishGreen;
		extern const glm::vec4 redBrown;
		extern const glm::vec4 greenishBrown;
		extern const glm::vec4 pumpkin;
		extern const glm::vec4 pineGreen;
		extern const glm::vec4 charcoal;
		extern const glm::vec4 babyPink;
		extern const glm::vec4 cornflower;
		extern const glm::vec4 blueViolet;
		extern const glm::vec4 chocolate;
		extern const glm::vec4 greyishGreen;
		extern const glm::vec4 scarlet;
		extern const glm::vec4 greenYellow_;
		extern const glm::vec4 darkOlive;
		extern const glm::vec4 sienna;
		extern const glm::vec4 pastelPurple;
		extern const glm::vec4 terracotta;
		extern const glm::vec4 aquaBlue;
		extern const glm::vec4 sageGreen;
		extern const glm::vec4 bloodRed;
		extern const glm::vec4 deepPink;
		extern const glm::vec4 grass;
		extern const glm::vec4 moss;
		extern const glm::vec4 pastelBlue;
		extern const glm::vec4 bluishGreen;
		extern const glm::vec4 greenBlue__;
		extern const glm::vec4 darkTan;
		extern const glm::vec4 greenishBlue;
		extern const glm::vec4 paleOrange;
		extern const glm::vec4 vomit;
		extern const glm::vec4 forrestGreen;
		extern const glm::vec4 darkLavender;
		extern const glm::vec4 darkViolet;
		extern const glm::vec4 purpleBlue_;
		extern const glm::vec4 darkCyan;
		extern const glm::vec4 oliveDrab;
		extern const glm::vec4 pinkish;
		extern const glm::vec4 cobalt;
		extern const glm::vec4 neonPurple;
		extern const glm::vec4 lightTurquoise;
		extern const glm::vec4 appleGreen;
		extern const glm::vec4 dullGreen;
		extern const glm::vec4 wine;
		extern const glm::vec4 powderBlue;
		extern const glm::vec4 offWhite;
		extern const glm::vec4 electricBlue;
		extern const glm::vec4 darkTurquoise;
		extern const glm::vec4 bluePurple_;
		extern const glm::vec4 azure;
		extern const glm::vec4 brightRed;
		extern const glm::vec4 pinkishRed;
		extern const glm::vec4 cornflowerBlue;
		extern const glm::vec4 lightOlive;
		extern const glm::vec4 grape;
		extern const glm::vec4 greyishBlue;
		extern const glm::vec4 purplishBlue;
		extern const glm::vec4 yellowishGreen;
		extern const glm::vec4 greenishYellow;
		extern const glm::vec4 mediumBlue;
		extern const glm::vec4 dustyRose;
		extern const glm::vec4 lightViolet;
		extern const glm::vec4 midnightBlue;
		extern const glm::vec4 bluishPurple;
		extern const glm::vec4 redOrange;
		extern const glm::vec4 darkMagenta;
		extern const glm::vec4 greenish;
		extern const glm::vec4 oceanBlue;
		extern const glm::vec4 coral;
		extern const glm::vec4 cream;
		extern const glm::vec4 reddishBrown;
		extern const glm::vec4 burntSienna;
		extern const glm::vec4 brick;
		extern const glm::vec4 sage;
		extern const glm::vec4 greyGreen_;
		extern const glm::vec4 white;
		extern const glm::vec4 robinsEggBlue;
		extern const glm::vec4 mossGreen;
		extern const glm::vec4 steelBlue;
		extern const glm::vec4 eggplant;
		extern const glm::vec4 lightYellow;
		extern const glm::vec4 leafGreen;
		extern const glm::vec4 lightGrey;
		extern const glm::vec4 puke;
		extern const glm::vec4 pinkishPurple;
		extern const glm::vec4 seaBlue;
		extern const glm::vec4 palePurple;
		extern const glm::vec4 slateBlue;
		extern const glm::vec4 blueGrey__;
		extern const glm::vec4 hunterGreen;
		extern const glm::vec4 fuchsia;
		extern const glm::vec4 crimson;
		extern const glm::vec4 paleYellow;
		extern const glm::vec4 ochre;
		extern const glm::vec4 mustardYellow;
		extern const glm::vec4 lightRed;
		extern const glm::vec4 cerulean;
		extern const glm::vec4 palePink;
		extern const glm::vec4 deepBlue;
		extern const glm::vec4 rust;
		extern const glm::vec4 lightTeal;
		extern const glm::vec4 slate;
		extern const glm::vec4 goldenrod;
		extern const glm::vec4 darkYellow;
		extern const glm::vec4 darkGrey;
		extern const glm::vec4 armyGreen;
		extern const glm::vec4 greyBlue__;
		extern const glm::vec4 seafoam;
		extern const glm::vec4 puce;
		extern const glm::vec4 springGreen;
		extern const glm::vec4 darkOrange;
		extern const glm::vec4 sand;
		extern const glm::vec4 pastelGreen;
		extern const glm::vec4 mint;
		extern const glm::vec4 lightOrange;
		extern const glm::vec4 brightPink;
		extern const glm::vec4 chartreuse;
		extern const glm::vec4 deepPurple;
		extern const glm::vec4 darkBrown;
		extern const glm::vec4 taupe;
		extern const glm::vec4 peaGreen;
		extern const glm::vec4 pukeGreen;
		extern const glm::vec4 kellyGreen;
		extern const glm::vec4 seafoamGreen;
		extern const glm::vec4 blueGreen__;
		extern const glm::vec4 khaki;
		extern const glm::vec4 burgundy;
		extern const glm::vec4 darkTeal;
		extern const glm::vec4 brickRed;
		extern const glm::vec4 royalPurple;
		extern const glm::vec4 plum;
		extern const glm::vec4 mintGreen;
		extern const glm::vec4 gold;
		extern const glm::vec4 babyBlue;
		extern const glm::vec4 yellowGreen__;
		extern const glm::vec4 brightPurple;
		extern const glm::vec4 darkRed;
		extern const glm::vec4 paleBlue;
		extern const glm::vec4 grassGreen;
		extern const glm::vec4 navy;
		extern const glm::vec4 aquaMarine_;
		extern const glm::vec4 burntOrange;
		extern const glm::vec4 neonGreen;
		extern const glm::vec4 brightBlue;
		extern const glm::vec4 rose;
		extern const glm::vec4 lightPink;
		extern const glm::vec4 mustard;
		extern const glm::vec4 indigo;
		extern const glm::vec4 lime;
		extern const glm::vec4 seaGreen;
		extern const glm::vec4 periwinkle;
		extern const glm::vec4 darkPink;
		extern const glm::vec4 oliveGreen;
		extern const glm::vec4 peach;
		extern const glm::vec4 paleGreen;
		extern const glm::vec4 lightBrown;
		extern const glm::vec4 hotPink;
		extern const glm::vec4 black;
		extern const glm::vec4 lilac;
		extern const glm::vec4 navyBlue;
		extern const glm::vec4 royalBlue;
		extern const glm::vec4 beige;
		extern const glm::vec4 salmon;
		extern const glm::vec4 olive;
		extern const glm::vec4 maroon;
		extern const glm::vec4 brightGreen;
		extern const glm::vec4 darkPurple;
		extern const glm::vec4 mauve;
		extern const glm::vec4 forestGreen;
		extern const glm::vec4 aqua;
		extern const glm::vec4 cyan;
		extern const glm::vec4 tan;
		extern const glm::vec4 darkBlue_;
		extern const glm::vec4 lavender;
		extern const glm::vec4 turquoise;
		extern const glm::vec4 darkGreen_;
		extern const glm::vec4 violet;
		extern const glm::vec4 lightPurple;
		extern const glm::vec4 limeGreen;
		extern const glm::vec4 grey;
		extern const glm::vec4 skyBlue;
		extern const glm::vec4 yellow;
		extern const glm::vec4 magenta;
		extern const glm::vec4 lightGreen_;
		extern const glm::vec4 orange;
		extern const glm::vec4 teal;
		extern const glm::vec4 lightBlue_;
		extern const glm::vec4 red;
		extern const glm::vec4 brown;
		extern const glm::vec4 pink;
		extern const glm::vec4 blue;
		extern const glm::vec4 green;
		extern const glm::vec4 purple;
	} // namespace Colors
} // namespace Nocturn::rendering
#endif