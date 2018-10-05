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
        /**
         * @brief Represents the state of the client
         */
        enum class Status {
            NotStarted,    ///< No request was made yet
            Running,       ///< A asynchronous request is running
            OK,            ///< The last request was successfull
            Aborted,       ///< The last request was aborted by the user
            Failed,        ///< The last request failed
            ResolveFailed, ///< The last request failed to resolve the host
            AccessDenied,  ///< The last request failed because the access to the ressource was denied
            InternalError  ///< The last request failed due to an internal error
        };

        /**
         * @brief Default constructor
         */
        HTTPClient();

        /**
         * @brief Destructor
         */
        ~HTTPClient();

        /** @name Performing requests */
        ///@{
        /**
         * @brief Starts a get request
         * @param  t_url The url to request
         * @return       The response body
         */
        const std::string get(const std::string& t_url);

        /**
         * @brief Starts an asynchronous get request
         * @param t_url The url to request
         */
        void getAsync(const std::string& t_url);

        /**
         * @brief Starts a get request and saves the response to a file
         * @param t_url      The url to request
         * @param t_filename The file to save to
         */
        void getToFile(const std::string& t_url, const std::string& t_filename);

        /**
         * @brief Starts a asynchronous get request and saves the response to a file
         * @param t_url      The url to request
         * @param t_filename The file to save to
         */
        void getToFileAsync(const std::string& t_url, const std::string& t_filename);

        /**
         * @brief Starts a post request
         * @param  t_url        The url to request
         * @param  t_parameters The post-parameters
         * @return              The response body
         */
        const std::string post(const std::string& t_url, const std::string& t_parameters);

        /**
         * @brief Starts a post request and saves the response to a file
         * @param t_url        The url to request
         * @param t_parameters The post-parameters
         * @param t_filename   The file to save to
         */
        void postAsync(const std::string& t_url, const std::string& t_parameters);

        /**
         * @brief Starts a post request and saves the response to a file
         * @param t_url        The url to request
         * @param t_parameters The post-parameters
         * @param t_filename   The file to save to
         */
        void postToFile(const std::string& t_url, const std::string& t_parameters, const std::string& t_filename);

        /**
         * @brief Starts a asynchronous post request and saves the response to a file
         * @param t_url        The url to request
         * @param t_parameters The post-parameters
         * @param t_filename   The file to save to
         */
        void postToFileAsync(const std::string& t_url, const std::string& t_parameters, const std::string& t_filename);
        ///@}

        /** @name Control methods */
        ///@{
        /**
         * @brief Waits for an asynchronous call to finish
         */
        void waitForFinish();

        /**
         * @brief Returns whether the last request is finished or not
         * @return `true` if it is finished, `false` if it is still running
         */
        bool isFinished();

        /**
         * @brief Cancels the current request
         */
        void cancel();
        ///@}

        /** @name Response handling */
        ///@{
        /**
         * @brief Returns the current state of the client
         * @return The current state
         */
        m3d::HTTPClient::Status getStatus();

        /**
         * @brief Returns the HTTP status code of the last request
         * @return The HTTP status code
         */
        int getStatusCode();

        /**
         * @brief Returns the response body of the last request
         * @return The response
         */
        const std::string getResponse();
        ///@}

        /** @name Progress */
        ///@{
        /**
         * @brief Returns the progress of the currently running request
         * @return The progress, ranging from 0.0 to 1.0
         */
        double getProgress();

        /**
         * @brief Returns the progress in bytes of the currently running request
         * @return The progress in bytes
         */
        double getProgressSize();

        /**
         * @brief Returns the total size of the response of the currently running request
         * @return The total size in bytes
         */
        double getTotalSize();
        ///@}

    private:
        struct Context {
            /* data */
            const std::string& m_url;
            bool m_post;
            const std::string m_parameters;
            bool m_toFile;
            const std::string& m_filename;
        };

        static size_t xferProgressFunction(void* t_p, double t_total, double t_downloaded, double, double);
        int progressFunction(double t_total, double t_downloaded);

        static size_t xferWriteFunction(char* t_ptr, size_t t_size, size_t t_nmemb, void* t_userdata);
        size_t writeFunction(char* t_ptr, size_t t_size, size_t t_nmemb);

        void callFunction(m3d::Parameter t_context);

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
