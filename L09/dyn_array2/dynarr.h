#ifndef DYNARR_H
#define DYNARR_H


class DynArr
{
    public:
        static const int DEFAULT_SIZE = 5;

        /** Default constructor */
        DynArr();
        /** Default destructor */
        ~DynArr();
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        DynArr& operator=(const DynArr& other);
        /** Access m_Size
         * \return The current value of m_Size
         */
        unsigned int getSize() { return m_Size; }
        /** Set m_Size
         * \param val New value to set
         */
        void setSize(unsigned int val);
        /** Access m_Capacity
         * \return The current value of m_Capacity
         */
        unsigned int getCapacity() { return m_Capacity; }
        /** Set m_Capacity
         * \param val New value to set
         */
        void setCapacity(unsigned int val) { m_Capacity = val; }
    protected:
    private:
        int * m_Arr;
        void resizeArr(unsigned int NewSize);
        unsigned int m_Size; //!< Member variable "m_Size"
        unsigned int m_Capacity; //!< Member variable "m_Capacity"
};

#endif // DYNARR_H
