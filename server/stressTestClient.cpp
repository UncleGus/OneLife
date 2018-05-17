

#include "minorGems/network/SocketClient.h"
#include "minorGems/system/Thread.h"
#include "minorGems/util/random/JenkinsRandomSource.h"
#include "minorGems/formats/encodingUtils.h"


JenkinsRandomSource randSource;



void usage() {
    printf( "Usage:\n" );
    printf( "stressTestClient server_address server_port email_prefix num_clients\n\n" );
    
    printf( "Example:\n" );
    printf( "stressTestClient onehouronelife.com 8005 dummy 100\n\n" );
    
    exit( 1 );
    }

int ourID;

typedef struct LiveObject {
        int id;
        int fatherID;
        int motherID;
        char *relationName;
        char male;
    } LiveObject;

SimpleVector<LiveObject> gameObjects;


LiveObject *getLiveObject( int inID ) {
    
    LiveObject *obj = NULL;

    for( int i=0; i<gameObjects.size(); i++ ) {
        
        LiveObject *o = gameObjects.getElement( i );
        
        if( o->id == inID ) {
            obj = o;
            break;
            }
        }
    return obj;
    }

LiveObject *getOurLiveObject() {
    
    return getLiveObject( ourID );
    }

char *getRelationName( LiveObject *inOurObject, LiveObject *inTheirObject ) {
    // start with an ID list of just this player
    int i = 0;
    int generation = 0;
    int totalPopulation = 1;
    char foundPerson = false;
    SimpleVector<int> ourLin;
    ourLin.push_back( inOurObject->id );

    while( i < ourLin.size() ) {
        printf("Looking at ourLin index %d\n", i);
        // get member at i in list, if there is a member there

        if( i == totalPopulation ) {
            printf("This is the start of a new generation\n");
            // looking at a new generation
            if( ! foundPerson ) {
                printf("The generation we just traversed was empty, stopping here\n");
                // the 'generation' we just traversed was all empty members (-1)
                break;
            }
            generation++;
            totalPopulation += 1 << generation;
            foundPerson = false;
            printf("This is generation %d, containing %d people, with %d people in total in the tree\n", generation, 1 << generation, totalPopulation);
        }
        int currentID = ourLin.getElementDirect( i );
        printf("This person's id is %d\n", currentID);
        if( currentID != -1 ) {
            foundPerson = true;
            LiveObject *currentMember = getLiveObject( currentID );
            printf("This is a real person with a father of %d and mother of %d, who are being added to the tree\n", currentMember->fatherID, currentMember->motherID);
            // add member's father to end of list
            ourLin.push_back( currentMember->fatherID );
            // add member's mother to end of list
            ourLin.push_back( currentMember->motherID );
        } else {
            printf("This is nobody, adding -1 as father and mother to the tree\n");
            // add -1 for "nobody"
            ourLin.push_back( -1 );
            ourLin.push_back( -1 );
        }
        i++;
    }

    while( ourLin.getElementDirect( ourLin.size() -1 ) == -1 ) {
        ourLin.shrink(ourLin.size() - 1 );
    }

    printf("Our family tree is:\n");
    for( int i=0; i<ourLin.size(); i++ ) {
        printf("%d ", ourLin.getElementDirect( i ));
    }
    printf("\n");

    // start with an ID list of just that player
    i = 0;
    foundPerson = false;
    SimpleVector<int> theirLin;
    theirLin.push_back( inTheirObject->id );

    while( i < theirLin.size() ) {
        printf("Looking at theirLin index %d\n", i);
        // get member at i in list, if there is a member there

        if( i == totalPopulation ) {
            printf("This is the start of a new generation\n");
            // looking at a new generation
            if( ! foundPerson ) {
                printf("The generation we just traversed was empty, stopping here\n");
                // the 'generation' we just traversed was all empty members (-1)
                break;
            }
            generation++;
            totalPopulation += 1 << generation;
            foundPerson = false;
            printf("This is generation %d, containing %d people, with %d people in total in the tree\n", generation, 1 << generation, totalPopulation);
        }
        int currentID = theirLin.getElementDirect( i );
        printf("This person's id is %d\n", currentID);
        if( currentID != -1 ) {
            foundPerson = true;
            LiveObject *currentMember = getLiveObject( currentID );
            printf("This is a real person with a father of %d and mother of %d, who are being added to the tree\n", currentMember->fatherID, currentMember->motherID);
            // add member's father to end of list
            theirLin.push_back( currentMember->fatherID );
            // add member's mother to end of list
            theirLin.push_back( currentMember->motherID );
        } else {
            printf("This is nobody, adding -1 as father and mother to the tree\n");
            // add -1 for "nobody"
            theirLin.push_back( -1 );
            theirLin.push_back( -1 );
        }
        i++;
    }

    while( theirLin.getElementDirect( theirLin.size() -1 ) == -1 ) {
        theirLin.shrink(theirLin.size() - 1 );
    }

    printf("Their family tree is:\n");
    for( int i=0; i<theirLin.size(); i++ ) {
        printf("%d ", theirLin.getElementDirect( i ));
    }
    printf("\n");

    int ourCommonAncestorIndex = 0;
    int theirCommonAncestorIndex = 0;
    int commonAncestorID = -1;

    for( int i = 0; i < ourLin.size(); i++ ) {
        if( commonAncestorID != -1 ) {
            break;
        }
        int ourCurrentMember = ourLin.getElementDirect( i );
        if( ourCurrentMember == -1 ) {
            continue;
        }
        for( int j = 0; j < theirLin.size(); j++ ) {
            int theirCurrentMember = theirLin.getElementDirect( j );
            if( theirCurrentMember == -1 ) {
                continue;
            }
            if( ourCurrentMember == theirCurrentMember ) {
                commonAncestorID = ourCurrentMember;
                ourCommonAncestorIndex = i;
                theirCommonAncestorIndex = j;
                break;
            }
        }
    }

    if ( commonAncestorID == -1 ) {
        return NULL;
    }

    int ourDistanceToCommonAncestor = 0;
    int theirDistanceToCommonAncestor = 0;
    while ( 1 << ( ourDistanceToCommonAncestor + 1 ) <= ( ourCommonAncestorIndex + 1 ) ) {
        ourDistanceToCommonAncestor++;
    }
    while ( 1 << ( theirDistanceToCommonAncestor + 1 ) <= ( theirCommonAncestorIndex + 1 ) ) {
        theirDistanceToCommonAncestor++;
    }

    const char *main = "";
    char grand = false;
    int numGreats = 0;
    int cousinNum = 0;
    int cousinRemovedNum = 0;
    char theyMale = inTheirObject->male;

    char big = false;
    char little = false;
    char twin = false;
    char identical = false;

    if( ourDistanceToCommonAncestor == 0 ) {
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
        cousinRemovedNum = abs( ourDistanceToCommonAncestor - theirDistanceToCommonAncestor );
    }


    SimpleVector<char> buffer;
    
    buffer.appendElementString( "your" );
    buffer.appendElementString( " " );

    for( int i=0; i<numGreats; i++ ) {
        buffer.appendElementString( "great" );
        }
    if( grand ) {
        buffer.appendElementString( "grand" );
        }
    
    if( cousinNum > 0 ) {
        int remainingCousinNum = cousinNum;

        if( cousinNum >= 30 ) {
            buffer.appendElementString( "distant" );
            remainingCousinNum = 0;
            }
        
        if( cousinNum > 20 && cousinNum < 30 ) {
            buffer.appendElementString( "twenty" );
            remainingCousinNum = cousinNum - 20;
            }

        if( remainingCousinNum > 0  ) {
            char *numth = autoSprintf( "%dth", remainingCousinNum );
            buffer.appendElementString( numth );
            delete [] numth;
            }
        buffer.appendElementString( " " );
        }

    if( little ) {
        buffer.appendElementString( "little" );
        buffer.appendElementString( " " );
        }
    else if( big ) {
        buffer.appendElementString( "big" );
        buffer.appendElementString( " " );
        }
    else if( twin ) {
        if( identical ) {
            buffer.appendElementString( "identical" );
            buffer.appendElementString( " " );
            }
        
        buffer.appendElementString( "twin" );
        buffer.appendElementString( " " );
        }
    
    
    buffer.appendElementString( main );
    
    if( cousinRemovedNum > 0 ) {
        buffer.appendElementString( " " );
        
        if( cousinRemovedNum > 9 ) {
            buffer.appendElementString( "many Times" );
            }
        else {
            char *numTimes = autoSprintf( "%d Times", cousinRemovedNum );
            buffer.appendElementString( numTimes );
            delete [] numTimes;
            }
        buffer.appendElementString( " " );
        buffer.appendElementString( "removed" );
        }

    printf("This person is %s\n", buffer.getElementString());
    return buffer.getElementString();
    }


typedef struct Client {
        int i;
        
        Socket *sock;
        SimpleVector<unsigned char> buffer;
        
        int skipCompressedData;
        
        char pendingCMData;
        int pendingCMCompressedSize;
        int pendingCMDecompressedSize;

        int id;
        int x, y;

        char moving;
        char dead;
        char disconnected;
        
    } Client;



// NULL if no message read
char *getNextMessage( Client *inC ) {

    if( inC->skipCompressedData > 0 && inC->buffer.size() > 0 ) {
        int numToDelete = inC->skipCompressedData;
        
        if( numToDelete > inC->buffer.size() ) {
            numToDelete = inC->buffer.size();
            }
        
        inC->buffer.deleteStartElements( numToDelete );
        inC->skipCompressedData -= numToDelete;
        }
    

    if( inC->skipCompressedData > 0 ) {
        printf( "Client %d still needs to skip %d compressed bytes\n",
                inC->i, inC->skipCompressedData );
        Thread::staticSleep( 1000 );
        
        unsigned char buffer[512];
    
        int nextReadSize = inC->skipCompressedData;
        
        if( nextReadSize > 512 ) {
            nextReadSize = 512;
            }
        int numRead = nextReadSize;
        
        while( numRead == nextReadSize && nextReadSize > 0 ) {
            nextReadSize = inC->skipCompressedData;
        
            if( nextReadSize > 512 ) {
                nextReadSize = 512;
                }

            numRead = inC->sock->receive( buffer, nextReadSize, 0 );
            
            if( numRead == -1 ) {
                inC->disconnected = true;
                }

            if( numRead > 0 ) {
                inC->skipCompressedData -= numRead;
                }
            }

        if( numRead != nextReadSize && nextReadSize > 0 ) {
            // timed out waiting for rest of compressed data
            return NULL;
            }
        }
    
    
    // read all available data
    unsigned char buffer[512];
    
    int numRead = inC->sock->receive( buffer, 512, 0 );

    if( numRead == -1 ) {
        inC->disconnected = true;
        }
    
    
    while( numRead > 0 ) {
        inC->buffer.appendArray( buffer, numRead );
        numRead = inC->sock->receive( buffer, 512, 0 );
        
        if( numRead == -1 ) {
            inC->disconnected = true;
            }
        }


    if( inC->pendingCMData ) {
        if( inC->buffer.size() >= inC->pendingCMCompressedSize ) {
            inC->pendingCMData = false;
            
            unsigned char *compressedData = 
                new unsigned char[ inC->pendingCMCompressedSize ];
            
            for( int i=0; i<inC->pendingCMCompressedSize; i++ ) {
                compressedData[i] = inC->buffer.getElementDirect( i );
                }
            inC->buffer.deleteStartElements( inC->pendingCMCompressedSize );
            
            unsigned char *decompressedMessage =
                zipDecompress( compressedData, 
                               inC->pendingCMCompressedSize,
                               inC->pendingCMDecompressedSize );

            delete [] compressedData;

            if( decompressedMessage == NULL ) {
                printf( "Decompressing CM message failed\n" );
                return NULL;
                }
            else {
                char *textMessage = 
                    new char[ inC->pendingCMDecompressedSize + 1 ];
                memcpy( textMessage, decompressedMessage,
                       inC->pendingCMDecompressedSize );
                textMessage[ inC->pendingCMDecompressedSize ] = '\0';
                
                delete [] decompressedMessage;
                
                return textMessage;
                }
            }
        else {
            // wait for more data to arrive
            return NULL;
            }
        }




    // find first terminal character #
    int index = inC->buffer.getElementIndex( '#' );
        
    if( index == -1 ) {
        return NULL;
        }
    

    char *message = new char[ index + 1 ];
    
    // all but terminal character
    for( int i=0; i<index; i++ ) {
        message[i] = (char)( inC->buffer.getElementDirect( i ) );
        }
    
    // delete from buffer, including terminal character
    inC->buffer.deleteStartElements( index + 1 );

    
    message[ index ] = '\0';
    
    if( strstr( message, "CM" ) == message ) {
        inC->pendingCMData = true;
        
        sscanf( message, "CM\n%d %d\n", 
                &( inC->pendingCMDecompressedSize ), 
                &( inC->pendingCMCompressedSize ) );


        delete [] message;
        
        return NULL;
        }
    

    return message;
    }



void parsePlayerUpdateMessage( Client *inC, char *inMessageLine ) {
    SimpleVector<char*> *tokens = tokenizeString( inMessageLine );

    //printf( "\n\nParsing PU line: %s\n\n", inMessageLine );
    
    if( tokens->size() > 16 ) {
        int id = -1;
        sscanf( tokens->getElementDirect(0), "%d", &( id ) );
    
        if( inC->id == -1 ) {
            inC->id = id;
            }
        
        if( inC->id == id ) {
            // update pos
            
            if( inC->moving ) {
                //printf( "Client %d done moving\n", inC->i );
                }
            if( strcmp( tokens->getElementDirect(14), "X" ) == 0 ) {
                // dead
                inC->dead = true;
                printf( "Client %d died with PU message:  %s\n",
                        inC->i, inMessageLine );
                }
            else {
                sscanf( tokens->getElementDirect(14), "%d", &( inC->x ) );
                sscanf( tokens->getElementDirect(15), "%d", &( inC->y ) );
                inC->moving = false;
                }
            }
        }
    
    
    tokens->deallocateStringElements();
    delete tokens;
    }





int main( int inNumArgs, char **inArgs ) {
    
    if( inNumArgs != 5 ) {
        usage();
        }
    
    char *address = inArgs[1];
    
    int port = 8005;
    sscanf( inArgs[2], "%d", &port );
    
    char *emailPrefix = inArgs[3];

    int numClients = 1;
    sscanf( inArgs[4], "%d", &numClients );

    
    Client *connections = new Client[ numClients ];
    
    // first, connect each
    int numConnected = 0;
    
    for( int i=0; i<numClients; i++ ) {
        connections[i].i = i;
        connections[i].id = -1;
        connections[i].skipCompressedData = 0;
        connections[i].pendingCMData = false;
        connections[i].moving = false;
        connections[i].dead = false;
        connections[i].disconnected = false;

        HostAddress a( stringDuplicate( address ), port );
        

        char timeout =  false;
        connections[i].sock = 
            SocketClient::connectToServer( &a, 5000, &timeout );

        if( timeout ) {
            printf( "Client %d timed out when trying to connect\n", i );
            delete connections[i].sock;
            connections[i].sock = NULL;
            continue;
            }
    
        if( connections[i].sock != NULL ) {
            numConnected ++;
            
            char *email = autoSprintf( "%s_%d@dummy.com", emailPrefix, i );

            printf( "Client %d connected, logging in with email %s\n", i,
                    email );

            
            char *message = autoSprintf( "LOGIN %s aaaa aaaa#",
                                         email );
            
            connections[i].sock->send( (unsigned char*)message, 
                                       strlen( message ), true, false );
            
            delete [] message;
            delete [] email;
            }
        else {
            printf( "Client %d failed to connect\n", i );
            }
        }

    
    // process messages
    while( numConnected > 0 ) {
        numConnected = 0;
        
        for( int i=0; i<numClients; i++ ) {
            if( connections[i].sock == NULL ) {
                continue;
                }
            numConnected ++;
        
            if( true || connections[i].id == -1) {
                // still waiting for first PU

                if( connections[i].disconnected ) {
                    printf( "Client %d lost connection\n", i );

                    delete connections[i].sock;
                    connections[i].sock = NULL;
                    continue;
                    }

                char *message = getNextMessage( &( connections[i] ) );

                if( message != NULL ) {
                    printf( "Client %d got message:\n%s\n\n", i, message );
                    
                    if( strstr( message, "MC" ) == message ) {
                        //printf( "Client %d got first map chunk\n", i );

                        int sizeX, sizeY, x, y, binarySize, compSize;
                        sscanf( message, "MC\n%d %d %d %d\n%d %d\n", 
                                &sizeX, &sizeY,
                                &x, &y, &binarySize, &compSize );
                    
                        connections[i].skipCompressedData = compSize;
                        }
                    else if( strstr( message, "PU" ) == message ) {
                        // PU message!
                    

                        // last line describes us

                        int numLines;
                        char **lines = split( message, "\n", &numLines );
                    
                        if( numLines > 2 ) {
                        
                            // first line is about us
                            parsePlayerUpdateMessage( &( connections[i] ),
                                                      lines[ numLines - 2 ] );
                            }
                    
                        printf( "Client %d got first player update, "
                                "pid = %d, pos = %d,%d\n", i, 
                                connections[i].id,
                                connections[i].x, 
                                connections[i].y );


                        
                        for( int p=0; p<numLines; p++ ) {
                            delete [] lines[p];
                            }
                        delete [] lines;
                        } else if ( strstr( message, "LN" ) == message ) {
                            int numLines;
                            char **lines = split( message, "\n", &numLines );
                            
                            if( numLines > 0 ) {
                                // skip first
                                delete [] lines[0];
                                }
                            
                            
                            for( int i=1; i<numLines; i++ ) {

                                int id;
                                int fatherID;
                                int motherID;
                                int numRead = sscanf( lines[i], "%d %d %d",
                                                    &( id ), &( fatherID ), &( motherID ) );

                                // add LiveObject if it doesn't already exist
                                if( getLiveObject( id ) == NULL ) {
                                    LiveObject n;
                                    n.id = id;
                                    n.fatherID = fatherID;
                                    n.motherID = motherID;
                                    n.relationName = NULL;
                                    if( id % 2 == 0 ) {
                                        n.male = true;
                                    } else {
                                        n.male = false;
                                    }
                                    gameObjects.push_back( n );
                                }

                                if( numRead == 3 ) {
                                    for( int j=0; j<gameObjects.size(); j++ ) {
                                        LiveObject *existing = gameObjects.getElement(j);
                                        if( existing->id == id ) {
                                            printf("Setting player %d father to %d and mother to %d\n", existing->id, fatherID, motherID );
                                            existing->fatherID = fatherID;
                                            existing->motherID = motherID;
                                            break;
                                            }
                                        }
                                    
                                    }
                                
                                delete [] lines[i];
                                }
                            delete [] lines;

                            // after a LINEAGE message, we should have lineage for all
                            // players
                            
                            // now process each one and generate relation string
                            LiveObject *ourObject = getOurLiveObject();
                            
                            for( int j=0; j<gameObjects.size(); j++ ) {
                                if( gameObjects.getElement(j)->id != ourID ) {
                                            
                                    LiveObject *other = gameObjects.getElement(j);
                                
                                    if( other->relationName == NULL ) {
                                        
                                        /*
                                        // test
                                        ourObject->lineage.deleteAll();
                                        other->lineage.deleteAll();
                                        
                                        int cousinNum = 25;
                                        int removeNum = 5;
                                        
                                        for( int i=0; i<=cousinNum; i++ ) {    
                                            ourObject->lineage.push_back( i );
                                            }

                                        for( int i=0; i<=cousinNum - removeNum; i++ ) {    
                                            other->lineage.push_back( 100 + i );
                                            }
                                        other->lineage.push_back( cousinNum );
                                        */
                                        other->relationName = getRelationName( ourObject,
                                                                            other );
                                        }
                                    }
                                }
                            }
                        }
                    delete [] message;
                    }                
            else {
                // player is live
                
                if( connections[i].dead ) {
                    printf( "Client %d died, closing connection\n", i );

                    delete connections[i].sock;
                    connections[i].sock = NULL;
                    continue;
                    }
                if( connections[i].disconnected ) {
                    printf( "Client %d lost connection\n", i );

                    delete connections[i].sock;
                    connections[i].sock = NULL;
                    continue;
                    }


                if( !connections[i].moving ) {
                
                    // make a move

                    connections[i].moving = true;
                
                    //printf( "Client %d starting move\n", i );
                    

                    int xDelt = 0;
                    int yDelt = 0;
                
                    while( xDelt == 0 && yDelt == 0 ) {
                        xDelt = randSource.getRandomBoundedInt( -1, 1 );
                        yDelt = randSource.getRandomBoundedInt( -1, 1 );
                        }
                
                
                    char *message = autoSprintf( "MOVE %d %d %d %d#",
                                                 connections[i].x,
                                                 connections[i].y,
                                                 xDelt, yDelt );
                
                    connections[i].sock->send( (unsigned char*)message, 
                                               strlen( message ), true, false );
                
                    delete [] message;
                    }

                char *message = getNextMessage( &( connections[i] ) );
        
                if( message != NULL ) {
                    if( strstr( message, "MC" ) == message ) {
                    
                        int sizeX, sizeY, x, y, binarySize, compSize;
                        sscanf( message, "MC\n%d %d %d %d\n%d %d\n", 
                                &sizeX, &sizeY,
                                &x, &y, &binarySize, &compSize );
                    
                        connections[i].skipCompressedData = compSize;
                        }
                    else if( strstr( message, "PU" ) == message ) {
                        // PU message!

                        int numLines;
                        char **lines = split( message, "\n", &numLines );
                    
                        for( int p=1; p<numLines-1; p++ ) {
                            parsePlayerUpdateMessage( &( connections[i] ),
                                                      lines[p] );
                            }

                        for( int p=0; p<numLines; p++ ) {
                            delete [] lines[p];
                            }
                        delete [] lines;
                        }
                    delete [] message;
                    }
            
                }
            }
        }
    
    printf( "No more clients connected\n" );
    
    for( int i=0; i<numClients; i++ ) {
        if( connections[i].sock != NULL ) {
            delete connections[i].sock;
            }
        }
    delete [] connections;
    
    return 1;
    }
