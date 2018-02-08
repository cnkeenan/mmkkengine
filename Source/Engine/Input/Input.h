#if !defined(INPUT_H)

class Input
{
public:
    virtual ~Input() {}
    virtual void execute() = 0;
};

#define INPUT_H

#endif
