#include "Image.hpp"


Image::Image(const char* filename, int dChannels){
        this->filename = filename;    
        this->dChannels = dChannels;
}

unsigned char* Image::load(){

    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, dChannels);
    if(!data){
        std::cout<<"image loading failed, "<<stbi_failure_reason();
    }
    else{
        this->data = data;
        return data;
    }

}

void Image::free(){

    stbi_image_free(this->data);
}
