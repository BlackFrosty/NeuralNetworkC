#ifndef FILE_MGMT_H
#define FILE_MGMT_H

#define MAGIC_IMAGE_FILE 0x00000803
#define MAGIC_LABEL_FILE 0x00000801

/**
 * Structure de l'entête du fichier d'images
 * */
typedef struct 
{
	char cMagic[4];
	int iNombreBitmaps;
	int iLargeurBitmap;
	int iHauteurBitmat;
} entete_image_t;
/**
 * suivi de iNombreBitmaps * (iLargeurBitmap * iHauteurBitmap unsigned char);

/**
 * Structure de l'entête du fichier d'étiquettes
 */
typedef struct 
{
	char cMagic[4];
	int iNombreBitmaps;
} entete_label_t;
/**
 *  Suivi de iNombreBitmatps unsigned char contenant la valeur correspondant à l'étiquette (0-9)
 */

#endif
