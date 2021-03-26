#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    //// STUDENT CODE
    ////
    // copy constructor
    ChatBot(const ChatBot &source) {

        //deep copy (owned) 
        //_image = new wxBitmap(*source._image);//copy constructor
       //*_image = (*source)._image;            //copy assignment operator
       if (source._image != NULL) {
           //_image = new wxBitmap(source._image->GetPixbuf(), source._image->GetDepth());
           _image = new wxBitmap(*(source._image));
       }
        _image->SaveFile("bot.png", wxBITMAP_TYPE_PNG);
        //shallow copys (not owned)
        _currentNode = source._currentNode;
        _rootNode = source._rootNode;
        _chatLogic = source._chatLogic;
        std::cout << "ChatBot Copy Constructor" << std::endl;
    }

    //copy assignment operator
    ChatBot &operator=(const ChatBot &source) {
        if (this == &source) {
            return *this;
        }
        //owned
        if(_image != NULL)
            delete _image;
        //assign data from source
        if (source._image != NULL) {
           _image = new wxBitmap(*(source._image));
        };

        //not owned
        _currentNode = source._currentNode;
        _rootNode = source._rootNode;
        _chatLogic = source._chatLogic;

        std::cout << "ChatBot Copy Assignment Operator" << std::endl;

        return *this;

    }

    //move constructor
    ChatBot(ChatBot &&source) {
        std::cout << "MOVING instance " << &source << " to instance " << this << std::endl;

       
        _image = source._image;
        _currentNode = source._currentNode;
        _rootNode = source._rootNode;
        _chatLogic = source._chatLogic;
        
        source._image = nullptr;
        source._currentNode = nullptr;
        source._rootNode = nullptr;
        source._chatLogic = nullptr;

    }

    //move assignment operator
    ChatBot &operator=(ChatBot &&source) {
        std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;

        //owned
        delete _image;
        _image = source._image;

        //not owned
        _currentNode = source._currentNode;
        _rootNode = source._rootNode;
        _chatLogic = source._chatLogic;
        
        source._image = nullptr;
        source._currentNode = nullptr;
        source._rootNode = nullptr;
        source._chatLogic = nullptr;        

        return *this;
    }
    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */