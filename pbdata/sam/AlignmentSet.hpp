#ifndef _BLASR_SAM_ALIGNMENT_SET_HPP_
#define _BLASR_SAM_ALIGNMENT_SET_HPP_

#include <map>
#include <string>
#include <vector>

#include <pbdata/FASTASequence.hpp>
#include <pbdata/sam/ReadGroup.hpp>
#include <pbdata/sam/ReferenceSequence.hpp>
#include <pbdata/sam/SAMAlignment.hpp>
#include <pbdata/sam/SAMHeader.hpp>

template <typename T_ReferenceSequence = SAMReferenceSequence, typename T_ReadGroup = SAMReadGroup,
          typename T_Alignment = SAMAlignment>
class AlignmentSet
{
public:
    SAMHeader header;
    std::vector<T_ReferenceSequence> references;
    std::vector<T_ReadGroup> readGroups;
    std::vector<T_Alignment> alignments;

    //
    //  Rearrange references such that they are placed in the same order
    //  as fastaReferences
    //
    void RearrangeReferences(std::vector<FASTASequence>& fastaReferences);
};

#include "AlignmentSetImpl.hpp"

#endif
