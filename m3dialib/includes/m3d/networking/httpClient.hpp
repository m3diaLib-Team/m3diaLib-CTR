/**
 * @file httpClient.hpp
 * @brief Defines the HTTPClient class
 */
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#pragma once
#include <3ds.h>
#include <curl/curl.h>
#include <string>
#include "m3d/core/thread.hpp"

namespace m3d {
    /**
     * @brief The HTTPClient class, used for performing HTTP requests
     */
    class HTTPClient {
    public:
        enum class Status {
            NotStarted,
            Running,
            OK,
            Aborted,
            Failed,
            ResolveFailed,
            AccessDenied,
            InternalError
        };

        HTTPClient();

        ~HTTPClient();

        /** @name Performing requests */
        ///@{
        const std::string get(const std::string& t_url);

        void getAsync(const std::string& t_url);

        void getToFile(const std::string& t_url, const std::string& t_filename);

        void getToFileAsync(const std::string& t_url, const std::string& t_filename);

        const std::string post(const std::string& t_url, const std::string& t_parameters);

        void postAsync(const std::string& t_url, const std::string& t_parameters);

        void postToFile(const std::string& t_url, const std::string& t_parameters, const std::string& t_filename);

        void postToFileAsync(const std::string& t_url, const std::string& t_parameters, const std::string& t_filename);
        ///@}

        /** @name Control methods */
        ///@{
        void waitForFinish();

        bool isFinished();

        void cancel();
        ///@}

        /** @name Response handling */
        ///@{
        m3d::HTTPClient::Status getStatus();

        int getStatusCode();

        const std::string getResponse();
        ///@}

        /** @name Progress */
        ///@{
        double getProgress();

        double getProgressSize();

        double getTotalSize();
        ///@}

    private:
        struct Context {
            /* data */
            const std::string& m_url;
            const std::string m_parameters;
            bool m_toFile;
            const std::string& m_filename;
        };

        static size_t xferProgressFunction(void* t_p, double t_total, double t_downloaded, double, double);
        int progressFunction(double t_total, double t_downloaded);

        static size_t xferWriteFunction(char* t_ptr, size_t t_size, size_t t_nmemb, void* t_userdata);
        size_t writeFunction(char* t_ptr, size_t t_size, size_t t_nmemb);

        void getFunction(m3d::Parameter t_context);

        /* data */
        std::atomic<bool> m_finished, m_cancel;
        m3d::Thread m_thread;
        CURL* m_handle;

        // size/progress
        std::atomic<double> m_progress, m_progressSize, m_totalSize;
        std::string m_response;

        // response status
        std::atomic<int> m_statusCode;
        m3d::HTTPClient::Status m_status;
    };
} /* m3d */


#endif /* end of include guard: HTTP_CLIENT_H */
