#ifndef IDELEGATOR_H
#define IDELEGATOR_H
class  IDelegator
{
public:
    ~IDelegator(){}

    virtual void OnAcknowledgement(const char* from, const char* args) = 0;
    virtual void OnException(const char* from, const char* args) = 0;
    virtual void OnNewVideoAvailable(const char* from, const char* args) = 0;
    virtual void OnSubscription(const char* from, const char* args) = 0;
    virtual void OnStartRecording(const char* from, const char* args) = 0;
    virtual void OnStopRecording(const char* from, const char* args) = 0;
    virtual void OnVideoFTPComplete(const char* from, const char* args) = 0;
    virtual void OnUnknownMessage(const char* from, const char* args) = 0;
};

#endif // IDELEGATOR_H
