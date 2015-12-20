// 15.3
// ListNode template definition

#ifndef LISTND_H
#define LISTND_H


template < class NODETYPE > class List; // forward declaration

template < class NODETYPE >
class ListNode {
	friend class List<NODETYPE>;
	public:
		ListNode( const NODETYPE & );
		NODETYPE getData() const;
	private:
		NODETYPE data;
		ListNode < NODETYPE > *nextPtr;

};

template <class NODETYPE>
ListNode <NODETYPE> ::ListNode( const NODETYPE &info)
	: data(info), nextPtr(0) { }
	
template <class NODETYPE>
NODETYPE ListNode <NODETYPE>::getData() const{
	return data;
}

#endif
