#include "ageControl.h"

#include <math.h>


static double babyHeadDownFactor = 0.6;

static double babyBodyDownFactor = 0.75;

static double oldHeadDownFactor = 0.35;

static double oldHeadForwardFactor = 2;

static int matureAge = 20;

static int oldAge = 40;

static int forceDeathAge = 60;


#include "minorGems/util/SettingsManager.h"


void initAgeControl() {
    babyHeadDownFactor = 
        SettingsManager::getFloatSetting( "babyHeadDownFactor", 0.6 );
    
    babyBodyDownFactor = 
        SettingsManager::getFloatSetting( "babyBodyDownFactor", 0.75 );

    oldHeadDownFactor = 
        SettingsManager::getFloatSetting( "oldHeadDownFactor", 0.35 );

    oldHeadForwardFactor = 
        SettingsManager::getFloatSetting( "oldHeadForwardFactor", 2 );
    
    matureAge =
        SettingsManager::getIntSetting( "matureAge", 20 );

    oldAge =
        SettingsManager::getIntSetting( "oldAge", 40 );

    forceDeathAge =
        SettingsManager::getIntSetting( "forceDeathAge", 60 );

    }




doublePair getAgeHeadOffset( double inAge, doublePair inHeadSpritePos,
                             doublePair inBodySpritePos,
                             doublePair inFrontFootSpritePos ) {
    if( inAge == -1 ) {
        return (doublePair){ 0, 0 };
        }
    
    if( inAge < matureAge ) {
        
        double maxHead = inHeadSpritePos.y - inBodySpritePos.y;
        
        double yOffset = ( ( matureAge - inAge ) / matureAge ) * babyHeadDownFactor * maxHead;
        
        
        return (doublePair){ 0, round( -yOffset ) };
        }
    

    if( inAge >= oldAge ) {
        
        if( inAge > forceDeathAge ) {
            // no worse after forceDeathAge
            inAge = forceDeathAge;
            }

        double maxHead = inHeadSpritePos.y - inBodySpritePos.y;
        
        double vertOffset = 
            ( ( inAge - oldAge ) / matureAge ) * oldHeadDownFactor * maxHead;
        
        double footOffset = inFrontFootSpritePos.x - inHeadSpritePos.x;
        
        double forwardOffset = 
            ( ( inAge - oldAge ) / matureAge ) * oldHeadForwardFactor * footOffset;

        return (doublePair){ round( forwardOffset ), round( -vertOffset ) };
        }

    return (doublePair){ 0, 0 };
    }



doublePair getAgeBodyOffset( double inAge, doublePair inBodySpritePos ) {
    if( inAge == -1 ) {
        return (doublePair){ 0, 0 };
        }
    
    if( inAge < matureAge ) {
        
        double maxBody = inBodySpritePos.y;
        
        double yOffset = ( ( matureAge - inAge ) / matureAge ) * babyBodyDownFactor * maxBody;
        
        
        return (doublePair){ 0, round( -yOffset ) };
        }

    return (doublePair){ 0, 0 };
    }

