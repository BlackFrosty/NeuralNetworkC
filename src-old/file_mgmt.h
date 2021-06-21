#ifndef FILE_MGMT_H
#define FILE_MGMT_H

#include <stdint.h>
#define MAGIC_IMAGE_FILE 0x00000803
#define MAGIC_LABEL_FILE 0x00000801

/**
 * Structure de l'entête du fichier d'images
 * */
typedef struct 
{
	uint32_t iMagic;
	uint32_t iNombreBitmaps;
	uint32_t iLargeurBitmap;
	uint32_t iHauteurBitmat;
} entete_image_t;
/**
 * suivi de iNombreBitmaps * (iLargeurBitmap * iHauteurBitmap unsigned char);
 */



/**
 * Structure de l'entête du fichier d'étiquettes
 */
typedef struct 
{
	uint32_t iMagic;
	uint32_t iNombreBitmaps;
} entete_label_t;
/**
 *  Suivi de iNombreBitmaps unsigned char contenant la valeur correspondant à l'étiquette (0-9)
 */

#endif
