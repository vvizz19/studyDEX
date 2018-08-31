/************************************************************************/
/* following struct definition, got from Web, If any question, call me : n0noper@qq.com  , 3KS  */
/************************************************************************/

#define	kSHA1DigestLen		20

typedef unsigned char		u1;
typedef unsigned short		u2;
typedef unsigned int		u4;
typedef unsigned __int64	u8;

enum {
    kDexTypeHeaderItem               = 0x0000,
	kDexTypeStringIdItem             = 0x0001,
	kDexTypeTypeIdItem               = 0x0002,
	kDexTypeProtoIdItem              = 0x0003,
	kDexTypeFieldIdItem              = 0x0004,
	kDexTypeMethodIdItem             = 0x0005,
	kDexTypeClassDefItem             = 0x0006,
	kDexTypeMapList                  = 0x1000,
	kDexTypeTypeList                 = 0x1001,
	kDexTypeAnnotationSetRefList     = 0x1002,
	kDexTypeAnnotationSetItem        = 0x1003,
	kDexTypeClassDataItem            = 0x2000,
	kDexTypeCodeItem                 = 0x2001,
	kDexTypeStringDataItem           = 0x2002,
	kDexTypeDebugInfoItem            = 0x2003,
	kDexTypeAnnotationItem           = 0x2004,
	kDexTypeEncodedArrayItem         = 0x2005,
	kDexTypeAnnotationsDirectoryItem = 0x2006
};



struct DexHeader {
    u1  magic[8];           /* includes version number */  
    u4  checksum;           /* adler32 checksum */  
    u1  signature[kSHA1DigestLen]; /* SHA-1 hash */
    u4  fileSize;           /* length of entire file */
    u4  headerSize;         /* offset to start of next section */
    u4  endianTag;
    u4  linkSize;
    u4  linkOff;
    u4  mapOff;				/* offset of DexMapList */
    u4  stringIdsSize;
    u4  stringIdsOff;
    u4  typeIdsSize;
    u4  typeIdsOff;
    u4  protoIdsSize;
    u4  protoIdsOff;
    u4  fieldIdsSize;
    u4  fieldIdsOff;
    u4  methodIdsSize;
    u4  methodIdsOff;
    u4  classDefsSize;
    u4  classDefsOff;
    u4  dataSize;
    u4  dataOff;
};



struct DexMapItem {   
    u2 type;      /* type of kDexType */
    u2 unused;  /* unused, for align the byte */
    u4 size;    /* size of type */
    u4 offset;  /* offset of Item */
};


struct DexMapList {
    u4 size;               /* size of DexMapItem */
    DexMapItem list[1];    /* data of DexMapItem */
};


struct DexStringId {
    u4 stringDataOff;   /* offset of string */
};


struct DexTypeId {
    u4 descriptorIdx;    /* Ids of type, point to index to DexStringId */
};


struct DexProtoId {
    u4 shortyIdx;   /* sign of proto, index to DexStringId */
    u4 returnTypeIdx;   /* return type of proto, index to DexTypeId */
    u4 parametersOff;   /* parameter of proto, offset of DexTypeList */
};


struct DexTypeItem {
    u2 typeIdx;    /* index of DexTypeId */
};

struct DexTypeList {
    u4 size;             /* size of DexTypeItem */
    DexTypeItem list[1]; /* data of DexTypeItem */
};




struct DexFieldId {
    u2 classIdx;   /* type of class, index of DexTypeId */
    u2 typeIdx;    /* type of field, index of DexTypeId */
    u4 nameIdx;    /* name of field, index of DexStringId */
};


struct DexMethodId {
    u2 classIdx;  /* type of class, index of DexTypeId */
    u2 protoIdx;  /* type of proto, index of DexProtoId */
    u4 nameIdx;   /* name of method, index of DexStringId */
};


struct DexClassDef {
    u4 classIdx;    /* type of class, index of DexTypeId */
    u4 accessFlags; /* flag of access */
    u4 superclassIdx;  /* type of super class, index of DexTypeId */
    u4 interfacesOff; /* interface, offset of DexTypeList */
    u4 sourceFileIdx; /* name of source file, index of DexStringId */
    u4 annotationsOff; /* annotation, offset of DexAnnotationsDirectoryItem */
    u4 classDataOff;   /* data of class, offset of DexClassData */
    u4 staticValuesOff;  /* static field, offset of DexEncodedArray */
};


struct DexClassDataHeader {
	u4 staticFieldsSize;  /* size of static field */
	u4 instanceFieldsSize; /* size of instance field */
	u4 directMethodsSize;  /* size of direct method */
	u4 virtualMethodsSize; /* size of virtual method */
};

struct DexField {
	u4 fieldIdx;    /* index of DexFieldId */
	u4 accessFlags; /* flag of access */
};

struct DexMethod {
	u4 methodIdx;   /* index of DexMethodId */
	u4 accessFlags; /* flag of access */
	u4 codeOff;     /* offset of DexCode */
};

struct DexCode {
	u2 registersSize;   /* size of register */
	u2 insSize;         /* size of parameter */
	u2 outsSize;        /* size of register which used to other method */
	u2 triesSize;       /* size of Try/Catch */
	u4 debugInfoOff;    /* offset of debug info */
	u4 insnsSize;       /* size of instruction */
	u2 insns[1];        /* data of instruction */
};


struct DexClassData {
    DexClassDataHeader header; 
    DexField* staticFields;    
    DexField* instanceFields;  
    DexMethod* directMethods;  
    DexMethod* virtualMethods; 
};

struct DexLink{

};	


struct DexFile {
    const DexHeader*    pHeader;
    const DexStringId*  pStringIds;
    const DexTypeId*    pTypeIds;
    const DexFieldId*   pFieldIds;
    const DexMethodId*  pMethodIds;
    const DexProtoId*   pProtoIds;
    const DexClassDef*  pClassDefs;
    const DexLink*      pLinkData;
};
		


