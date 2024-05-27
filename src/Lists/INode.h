//
// Created by grzegorz on 22.03.24.
//

#ifndef LISTY_INODE_H
#define LISTY_INODE_H

class INode {
public:
    virtual ~INode() = default;
    /**
     * Gets pionter to next INode
     * @return nullptr - cannot get or no pointer
     * @return pointer - success
     */
    virtual INode* getNext() = 0;

    /**
     * Gets pionter to previous INode
     * @return nullptr - cannot get or no pointer
     * @return pointer - success
     */
    virtual INode* getPrevious() = 0;

    /**
     * Sets pionter to next INode
     * @param _next
     * @return 1 - not available
     * @return 0 - success
     */
    virtual int setNext(INode* _next) = 0;

    /**
     * Sets pionter to previous INode
     * @param _next
     * @return 1 - not available
     * @return 0 - success
     */
    virtual int setPrevious(INode* _previous) = 0;
};


#endif //LISTY_INODE_H
