#ifndef IDELEGATOR_H
#define IDELEGATOR_H
#define UNUSED(x) (void)(x)
class  IDelegator
{
public:
    ~IDelegator(){}

    virtual void OnAcknowledgement(const char* from, const char* args) = 0;

    virtual void OnException(const char* from, const char* args) = 0;

    virtual void OnNewVideoAvailable(const char* from, const char* args){
        UNUSED(from); UNUSED(args);
    }
    virtual void OnSubscription(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnStartRecording(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnStopRecording(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnVideoFTPComplete(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnUnknownMessage(const char* from, const char* args) = 0;

    virtual void OnSourceIdle(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    //TODO: Should not be optional
    virtual void OnHandshake(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnHandshakeId(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnRequestSources(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}

    virtual void OnReplySources(const char* from, const char* args){
        UNUSED(from); UNUSED(args);}
};

#endif // IDELEGATOR_H
