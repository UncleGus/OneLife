gameObjects = [
    {
        id: 1,
        fatherID: 2,
        motherID: 3,
        male: true,
        age: 10,
        displayID: 1,
    },
    {
        id: 2, // father to 1
        fatherID: 4,
        motherID: 5,
        male: true,
        age: 30,
        displayID: 1,
    },
    {
        id: 3, // mother to 1
        fatherID: 6,
        motherID: 7,
        male: false,
        age: 30,
        displayID: 1,
    },
    {
        id: 4, // grandfather to 1
        fatherID: -1,
        motherID: -1,
        male: true,
        age: 50,
        displayID: 1,
    },
    {
        id: 5, // grandmother to 1
        fatherID: -1,
        motherID: -1,
        male: false,
        age: 50,
        displayID: 1,
    },
    {
        id: 6, // grandfather to 1
        fatherID: -1,
        motherID: -1,
        male: true,
        age: 50,
        displayID: 1,
    },
    {
        id: 7, // grandmother to 1
        fatherID: 13,
        motherID: 14,
        male: false,
        age: 50,
        displayID: 1,
    },
    {
        id: 8, // brother of 1
        fatherID: 2,
        motherID: 3,
        male: true,
        age: 11,
        displayID: 1,
    },
    {
        id: 9, // sister of 1
        fatherID: 2,
        motherID: 3,
        male: false,
        age: 9,
        displayID: 1,
    },
    {
        id: 10, // aunty to 1
        fatherID: 6,
        motherID: 7,
        male: false,
        age: 30,
        displayID: 1,
    },
    {
        id: 11, // no relation to 1
        fatherID: -1,
        motherID: -1,
        male: true,
        age: 30,
        displayID: 1,
    },
    {
        id: 12, // 1st cousin to 1
        fatherID: 10,
        motherID: 11,
        male: false,
        age: 10,
        displayID: 1,
    },
    {
        id: 13, // great grandfather to 1
        fatherID: -1,
        motherID: -1,
        male: true,
        age: 60,
        displayID: 1,
    },
    {
        id: 14, // great grandmother to 1
        fatherID: -1,
        motherID: -1,
        male: false,
        age: 60,
        displayID: 1,
    },
    {
        id: 15, // great uncle to 1
        fatherID: 13,
        motherID: 14,
        male: true,
        age: 50,
        displayID: 1,
    },
    {
        id: 16, // no relation to 1
        fatherID: -1,
        motherID: -1,
        male: false,
        age: 50,
        displayID: 1,
    },
    {
        id: 17, // 2nd cousin once removed
        fatherID: 15,
        motherID: 16,
        male: true,
        age: 30,
        displayID: 1,
    },
    {
        id: 18, // no relation to 1
        fatherID: -1,
        motherID: -1,
        male: false,
        age: 30,
        displayID: 1,
    },
    {
        id: 19, // 2nd cousin to 1
        fatherID: 17,
        motherID: 18,
        male: false,
        age: 10,
        displayID: 1,
    },
    {
        id: 20, // no relation to 1
        fatherID: -1,
        motherID: -1,
        male: true,
        age: 10,
        displayID: 1,
    },
    {
        id: 21, // 3rd cousin to 1
        fatherID: 20,
        motherID: 19,
        male: false,
        age: 1,
        displayID: 1,
    },
    {
        id: 22, // no relation (wife)
        fatherID: -1,
        motherID: -1,
        male: false,
        age: 10,
        displayID: 1,
    },
    {
        id: 23, // daughter to 1
        fatherID: 1,
        motherID: 22,
        male: false,
        age: 1,
        displayID: 1,
    },
]

const ourID = 23;
const theirID = 15;

const ourObject = gameObjects[ourID - 1];
const theirObject = gameObjects[theirID - 1];

let ourLin = [];
ourLin.push(ourObject.id);
let theirLin = [];
theirLin.push(theirObject.id);

const getGameObject = function(id) {
    for (const object of gameObjects) {
        if (object.id == id) {
            return object;
        }        
    }
    return null;
}

let i = 0;
let generation = 0;
let totalPopulation = 1;
let foundPerson = false;

while( i < ourLin.length ) {
    // console.log(`Looking at position ${i} of ${ourLin.length}, generation is ${generation}`);
    if( i == totalPopulation ) {
        // console.log('This is the start of a new generation');
        if( ! foundPerson ) {
            // console.log('Just traversed an entire generation without finding a real person');
            break;
        }
        generation++;
        totalPopulation += 1 << generation;
        foundPerson = false;
    }
    // console.log(`There are ${1 << generation} people in this generation`);
    // get member at i in list, if there is a member there
    const currentID = ourLin[i];
    // console.log(`currentID is ${currentID}`);
    if( currentID != -1 ) {
        foundPerson = true;
        const currentMember = getGameObject(currentID);
        // add member's father to end of list
        ourLin.push( currentMember.fatherID );
        // add member's mother to end of list
        ourLin.push( currentMember.motherID );
    } else {
        // add -1 for "nobody"
        ourLin.push( -1 );
        ourLin.push( -1 );
    }
    i++;
}

while( ourLin[ourLin.length -1] == -1 ) {
    ourLin.pop();
}

i = 0;
generation = 0;
totalPopulation = 1;
foundPerson = false;

while( i < theirLin.length ) {
    // console.log(`Looking at position ${i} of ${theirLin.length}, generation is ${generation}`);
    if( i == totalPopulation ) {
        // console.log('This is the start of a new generation');
        if( ! foundPerson ) {
            // console.log('Just traversed an entire generation without finding a real person');
            break;
        }
        generation++;
        totalPopulation += 1 << generation;
        foundPerson = false;
    }
    // console.log(`There are ${1 << generation} people in this generation`);
    // get member at i in list, if there is a member there
    const currentID = theirLin[i];
    // console.log(`currentID is ${currentID}`);
    if( currentID != -1 ) {
        foundPerson = true;
        const currentMember = getGameObject(currentID);
        // add member's father to end of list
        theirLin.push( currentMember.fatherID );
        // add member's mother to end of list
        theirLin.push( currentMember.motherID );
    } else {
        // add -1 for "nobody"
        theirLin.push( -1 );
        theirLin.push( -1 );
    }
    i++;
}

while( theirLin[theirLin.length -1] == -1 ) {
    theirLin.pop();
}

console.log(ourLin);
console.log(theirLin);

let ourCommonAncestorIndex = 0;
let theirCommonAncestorIndex = 0;
let commonAncestorID = -1;

for( let i = 0; i < ourLin.length; i++ ) {
    for( let j = 0; j < theirLin.length; j++ ) {
        if (commonAncestorID != -1) {
            break;
        }
        // console.log(`Comparing our position ${i} to their position ${j}`);
        // console.log(`Comparing ${ourLin[i]} to ${theirLin[j]}`);
        if( ourLin[i] == theirLin[j] ) {
            // console.log('Found a common ancestor');
            commonAncestorID = ourLin[i];
            ourCommonAncestorIndex = i;
            theirCommonAncestorIndex = j;
            break;
        }
    }
}

console.log(`Common ancestor is ${commonAncestorID}`);

let ourDistanceToCommonAncestor = 0;
let theirDistanceToCommonAncestor = 0;
while ( 1 << ( ourDistanceToCommonAncestor + 1 ) <= ( ourCommonAncestorIndex +1 ) ) {
    ourDistanceToCommonAncestor++;
}
while ( 1 << ( theirDistanceToCommonAncestor + 1 ) <= ( theirCommonAncestorIndex +1 ) ) {
    theirDistanceToCommonAncestor++;
}

console.log(`Our distance to common ancestor is ${ourDistanceToCommonAncestor}`);
console.log(`Their distance to common ancestor is ${theirDistanceToCommonAncestor}`);

let main = "";
let grand = false;
let numGreats = 0;
let cousinNum = 0;
let cousinRemovedNum = 0;
let theyMale = theirObject.male;

let big = false;
let little = false;
let twin = false;
let identical = false;

if (commonAncestorID == -1) {
    main = "no relation";
} else if( ourDistanceToCommonAncestor == 0 ) {
    // this is a direct descendant
    if( theyMale ) {
        main = "son";
        }
    else {
        main = "daughter";
        }
    if( theirDistanceToCommonAncestor > 1 ) {
        grand = true;
        numGreats = theirDistanceToCommonAncestor - 2;
    }
} else if ( theirDistanceToCommonAncestor == 0 ) {
    // this is a direct ancestor
    if( theyMale ) {
        main = "father";
        }
    else {
        main = "mother";
        }
    if( ourDistanceToCommonAncestor > 1 ) {
        grand = true;
        numGreats = ourDistanceToCommonAncestor - 2;
    }
} else if ( ourDistanceToCommonAncestor == theirDistanceToCommonAncestor ) {
    if ( ourDistanceToCommonAncestor == 1 ) {
        // this is a sibling
        if( theyMale ) {
            main = "brother";
            }
        else {
            main = "sister";
            }
        if( ourObject.age < theirObject.age - 0.1 ) {
            big = true;
            }
        else if( ourObject.age > theirObject.age + 0.1 ) {
            little = true;
            }
        else {
            // close enough together in age
            twin = true;
            
            if( ourObject.displayID == theirObject.displayID ) {
                identical = true;
                }
            }
    } else {
        // this is a cousin
        main = "cousin";
        cousinNum = ourDistanceToCommonAncestor - 1;
    }
} else if ( theirDistanceToCommonAncestor == 1 ) {
    // this is an aunt or uncle
    if( theyMale ) {
        main = "uncle";
        }
    else {
        main = "aunt";
        }
    if( ourDistanceToCommonAncestor > 2 ) {
        grand = true;
        numGreats = ourDistanceToCommonAncestor - 3;
    }
} else if ( ourDistanceToCommonAncestor == 1 ) {
    // this is a nephew or niece
    if( theyMale ) {
        main = "nephew";
        }
    else {
        main = "niece";
        }
    if( theirDistanceToCommonAncestor > 2 ) {
        grand = true;
        numGreats = theirDistanceToCommonAncestor - 3;
    }
} else {
    // this is a removed cousin
    main = "cousin";
    if ( ourDistanceToCommonAncestor < theirDistanceToCommonAncestor ) {
        cousinNum = ourDistanceToCommonAncestor;
    } else {
        cousinNum = theirDistanceToCommonAncestor;
    }
    cousinRemovedNum = Math.abs( ourDistanceToCommonAncestor - theirDistanceToCommonAncestor );
}

let buffer = "your ";

for( let i=0; i<numGreats; i++ ) {
    buffer += "great ";
    }
if( grand ) {
    buffer += "grand";
    }

if( cousinNum > 0 ) {
    let remainingCousinNum = cousinNum;

    if( cousinNum >= 30 ) {
        buffer += "distant";
        remainingCousinNum = 0;
        }
    
    if( cousinNum > 20 && cousinNum < 30 ) {
        buffer += "twenty";
        remainingCousinNum = cousinNum - 20;
        }

    if( remainingCousinNum > 0  ) {
        buffer += remainingCousinNum + 'th ';
        }
    }

if( little ) {
    buffer += "little ";
    }
else if( big ) {
    buffer += "big ";
    }
else if( twin ) {
    if( identical ) {
        buffer += "identical ";
        }
    
    buffer += "twin ";
    }


buffer += main;

if( cousinRemovedNum > 0 ) {
    buffer += " ";
    
    if( cousinRemovedNum > 9 ) {
        buffer += "many times";
        }
    else {
        buffer += cousinRemovedNum + " times removed";
        }
    }

console.log(buffer);