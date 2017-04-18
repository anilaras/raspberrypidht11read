#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
 
void read_dht11_dat(char hortctr)
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;

		if (hortctr == 0)
		{
					f = dht11_dat[2] * 9. / 5. + 32;
		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
		}
		else if (hortctr == 1)
		{
			printf( "Temperature = %d.%d C\n",dht11_dat[2], dht11_dat[3]);
		}else if (hortctr == 2)
		{
			printf( "Humidity = %d.%d\n",dht11_dat[0], dht11_dat[1]);
		}

	}else  {
		printf( "Data not good, skip\n" );
	}
}
 
int main( int argc, char **argv )
{
 

	if ( wiringPiSetup() == -1 )
		exit( 1 );
  
  if (argc < 2) // no arguments were passed
    {
                        while ( 1 )
        {
                read_dht11_dat(0);
                delay( 1000 ); 
        }
    }

    if (strcmp("-all", argv[1]) == 0 || strcmp("-a", argv[1]) == 0)
    {
              while ( 1 )
        {
                read_dht11_dat(0);
                delay( 1000 ); 
        }
    }
    else if (strcmp("-temp", argv[1]) == 0 || strcmp("-t", argv[1]) == 0)
    {
            while ( 1 )
        {
                read_dht11_dat(1);
                delay( 1000 ); 
        }
    }
    else if (strcmp("-humidity", argv[1]) == 0|| strcmp("-h", argv[1]) == 0)
    {
    	        while ( 1 )
        {
                read_dht11_dat(2);
                delay( 1000 ); 
        }
    }

	return(0);
}

