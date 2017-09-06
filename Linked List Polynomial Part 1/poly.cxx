#include "poly.h"
using namespace std;

// The member variables of a polynomial are usually going to be the coefficient, the
// exponent, forwards, and backwards. In a linked list the head_ptr is linked to the
// first polynomial with different variables it contains. It first reaches the coefficient
// of the polynomial which is the first variable in the list followed by the exponent, then the fore
// member function which will either determine if the forward node is NULL or then points to the next node
// in the linked list. Then followed by the backwards member function that will determine if the previous
// node exists or doesn't exist (NULL). This creates a functional linked list that holds polynomials
// that we can use in order to determine x placement values correctly and manipulate the places in which
// polynomials are listed with the highest degree exponent within the tail_ptr node and the lowest degree
// exponent (x^0) in the node that the head_ptr is connected to. 

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		EPSILON = std::numeric_limits<double>::epsilon();
		
		if(fabs(c) < EPSILON)
		{
			head_ptr = new polynode();
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else if(exponent == 0)
		{
			head_ptr = new polynode(c, 0, NULL, NULL);
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else
		{
			head_ptr = new polynode();
			tail_ptr = new polynode(c, exponent, NULL, head_ptr);
			head_ptr->set_fore(tail_ptr);
			current_degree = exponent;
		}
		recent_ptr = head_ptr;
    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		
		EPSILON = std::numeric_limits<double>::epsilon();
		
		if(this == &source)
			return *this;
		
		if(head_ptr != NULL)
			this->clear();
		
		unsigned int expo = 0;
		
		do
		{
			assign_coef(source.coefficient(expo), expo);
			expo = source.next_term(expo);
		}
		while(expo != 0);
		
		current_degree = source.degree();
		return *this;
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		
		this->head_ptr = new polynode();
		this->tail_ptr = head_ptr;
		*this = source;
    }

    polynomial::~polynomial()
    {
		clear();
		delete head_ptr;
		head_ptr = NULL;
    }

    void polynomial::clear()
    {
		polynode* handle;
		
		while(head_ptr->fore() != NULL)
		{
			handle = head_ptr->fore();
			delete head_ptr;
			head_ptr = handle;
		}
		
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		current_degree = 0;
		head_ptr->set_fore(NULL);
		head_ptr->set_back(NULL);
		recent_ptr = head_ptr;
		handle = NULL;
		
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		
		if(recent_ptr->exponent() != exponent)
			return 0.0;
		
		else
			return recent_ptr->coef();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);
		
		if(fabs(amount) < EPSILON)
			return;
			
		else if(recent_ptr->exponent() == exponent)
		{
			assign_coef((recent_ptr->coef() + amount), recent_ptr->exponent());
		}
		
		else
			assign_coef(amount, exponent); 
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		polynode* backwards = recent_ptr->back();
		polynode* forwards = recent_ptr->fore();
		
		if(fabs(coefficient) <= EPSILON)
			coefficient = 0;
		
		if(exponent == 0)
		{
			head_ptr->set_coef(coefficient);
			return;
		}
		
		else if(fabs(coefficient) < EPSILON)
		{
			if(exponent == recent_ptr->exponent())
			{
				if(recent_ptr == head_ptr)
				{
					recent_ptr->set_coef(0);
					return;
				}
				
				else if(recent_ptr->exponent() == current_degree)
				{
					recent_ptr = recent_ptr->back();
					recent_ptr->set_fore(NULL);
					delete tail_ptr;
					tail_ptr = recent_ptr;
					current_degree = tail_ptr->exponent();
				}
				
				else
				{
					forwards->set_back(backwards);
					backwards->set_fore(forwards);
					delete recent_ptr;
					set_recent(exponent);
				}
			}
			
			else
				return;
		}
		
		else if(exponent > current_degree)
		{
			polynode* helixNode = new polynode(coefficient, exponent, NULL, recent_ptr);
			recent_ptr->set_fore(helixNode);
			recent_ptr = helixNode;
			tail_ptr = helixNode;
			current_degree = exponent;
		}
		
		else if(recent_ptr->exponent() < exponent)
		{
			polynode* helixNode = new polynode(coefficient, exponent, forwards, recent_ptr);
			recent_ptr->set_fore(helixNode);
			forwards->set_back(helixNode);
			recent_ptr = helixNode;
		}
		
		else if(recent_ptr->exponent() < exponent)
		{
			polynode* helixNode = new polynode(coefficient, exponent, recent_ptr, backwards);
			recent_ptr->set_back(helixNode);
			backwards->set_fore(helixNode);
			recent_ptr = helixNode;
		}
		
		else
			recent_ptr->set_coef(coefficient);
    }

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		if(exponent >= current_degree)
			return 0;
		
		set_recent(exponent);
		
		if(recent_ptr->fore() == NULL)
			return 0;
			
		else
			return recent_ptr->fore()->exponent();
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if(exponent <= 0)
			return UINT_MAX;
		
		set_recent(exponent - 1);
		
		if(fabs(recent_ptr->coef()) < EPSILON)
			return UINT_MAX;
			
		if(recent_ptr == NULL)
			return UINT_MAX;
			
		else
			return recent_ptr->exponent();
    }
    
    void polynomial::set_recent(unsigned int exponent) const
    {
		if(exponent == 0)
		{
			recent_ptr = head_ptr;
			return;
		}
		
		else if(exponent > current_degree)
		{
			recent_ptr = tail_ptr;
			return;
		}
		
		else if(recent_ptr->exponent() == exponent)
			return;
			
		else if(recent_ptr->exponent() < exponent)
		{
			while(recent_ptr->fore() != NULL && recent_ptr->exponent() < exponent)
					recent_ptr = recent_ptr->fore();
					
				if(recent_ptr->exponent() > exponent)
					recent_ptr = recent_ptr->back();
		}
		
		else
		{
			while(recent_ptr->back() != NULL && recent_ptr->exponent() > exponent)
				recent_ptr = recent_ptr->back();
		}
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			
			if(expo != 0)
				out << " + ";
		}
		while(expo != 0);
		
		return out;
    }
    
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
	}
}
