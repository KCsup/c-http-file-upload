#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int make_file_post_req(char* url, char* file_path)
{
    printf("calling func\n");
    CURL* curl;
    CURLcode res;
    struct stat file_info;
    int fd; // file descriptor

    if(stat(file_path, &file_info) < 0)
    {
      return 1;
    }

    printf("opening file\n");

    fd = open(file_path, O_RDONLY);
    if(fd < 0)
      return 1;

    printf("File opened\n");

    curl = curl_easy_init();
    printf("curl initiated\n");
    if(curl == NULL)
    {
      curl_easy_cleanup(curl);
      close(fd);
      return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    printf("curl flags set\n");
    // not using verbose logging

    int status = 0;
    res = curl_easy_perform(curl);
    printf("%d\n", res);
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    printf("easy performed\n");
    
    // if(res != CURLE_OK)
    //   status = 1;
    
    curl_easy_cleanup(curl);
    printf("closing\n");
    close(fd);

    return status;
}

int make_post_req(char* url, char* post_fields)
{
    CURL* curl;
    CURLcode res;
    int result = 0;
    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_POST, 1L);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
      
      res = curl_easy_perform(curl);
      
      if(res != CURLE_OK)
        result = 1;

      curl_easy_cleanup(curl);
    }
    else
      result = 1;
      
    return result;
}

int main(int argc, char** argv)
{
    if(argc < 2) {
        printf("No arguments given.");
        return 1;
    }

    // for(int i = 1; i < argc; i++) {
    //     printf("%s\n", argv[i]);
    //     make_file_post_req("", "client.c");
    // }
    make_file_post_req(argv[1], "curl.c");

    return 0;
}
