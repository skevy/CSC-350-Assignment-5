#include <assert.h>
#include <fstream>
#include <string>

#include "Utility.hpp"
#include "TGA.hpp"

using namespace std;

namespace HabuTech {
    TGA::TGA(const std::string& name) : Texture(name) {
        meTextureType = TGA_TEXTURE_TYPE;
    }
    
    TGA::~TGA() {
        
    }
    
    bool TGA::Deserialize(unsigned char* cpHeader) {
        bool bReturnValue = false;
        
        this->mcID_Length = cpHeader[0];
        this->mcColorMapType = cpHeader[1];
        this->mcDataTypeCode = cpHeader[2];
        memcpy_s(&(this->msColorMapOrigin), sizeof(this->msColorMapOrigin), &(cpHeader[3]), 2);
        memcpy_s(&(this->msColorMapLength), sizeof(this->msColorMapLength), &(cpHeader[5]), 2);
        this->mcColorMapDepth = cpHeader[7];
        memcpy_s(&(this->msX_Origin), sizeof(this->msX_Origin), &(cpHeader[8]), 2);
        memcpy_s(&(this->msY_Origin), sizeof(this->msY_Origin), &(cpHeader[10]), 2);
        memcpy_s(&(this->msWidth), sizeof(this->msWidth), &(cpHeader[12]), 2);
        memcpy_s(&(this->msHeight), sizeof(this->msHeight), &(cpHeader[14]), 2);
        this->mcBitsPerPixel = cpHeader[16];
        this->mcImageDescription = cpHeader[17];
        
        Texture::musWidth = this->msWidth;
        Texture::musHeight = this->msHeight;
        Texture::mucDepthInBits = this->mcBitsPerPixel;
        Texture::mucDepthInBytes = this->mcBitsPerPixel / 8;
        
        return bReturnValue;
    }
    
    bool TGA::Load(ifstream& ifs) {
        bool bReturnValue = false;
        
        assert(ifs.is_open() && ifs.good());
        
        if(!ifs.is_open() || !ifs.good()) 
            return false;
        
        string label;
        string fileName;
        
        unsigned short usParameterCount = 0;
        
        ifs >> label;
        if(label == "File") {
            ifs >> fileName;
            ifstream ifsTGA;
            ifsTGA.open(fileName.c_str(), ios::binary);
            if(ifsTGA.is_open()) {
                unsigned char* pucHeader = new unsigned char[18];
                ifsTGA.read(reinterpret_cast<char*>(pucHeader), 18);
                this->Deserialize(pucHeader);
                
                if(Texture::mpImage)
                    delete [] Texture::mpImage;
                
                Texture::mpImage = new Color<unsigned char>[Texture::musWidth * Texture::musHeight];
                unsigned long ulBytesToRead = Texture::musWidth * Texture::musHeight * Texture::mucDepthInBytes;
                unsigned long ulBytesRead = 0UL;
                unsigned long ulTexelsRead = 0UL;
                Color<unsigned char> oTempColor;
                unsigned long ulIndex = 0;
                while(ulBytesRead < ulBytesToRead) {
                    char caTemp[3];
                    ifsTGA.read(&caTemp[0], Texture::mucDepthInBytes);
                    ulBytesRead += Texture::mucDepthInBytes;
                    Texture::mpImage[ulIndex].A(0);
                    Texture::mpImage[ulIndex].R(caTemp[2]);
                    Texture::mpImage[ulIndex].G(caTemp[1]);
                    Texture::mpImage[ulIndex].B(caTemp[0]);
                    ulIndex++;
                }
                
                delete [] pucHeader;
                
                if(ulBytesRead == ulBytesToRead)
                    bReturnValue = true;
            }
        }
        
        Texture::Initialize();
        
        return bReturnValue;
    }
}