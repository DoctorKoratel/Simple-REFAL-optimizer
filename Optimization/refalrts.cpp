#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <assert.h>

#include "refalrts.h"

#if 1
#  define VALID_LINKED( iter )
#else
#  define VALID_LINKED( iter ) valid_linked_aux( #iter, iter );
#endif

#ifndef SHOW_DEBUG
#define SHOW_DEBUG 0
#endif // ifdef SHOW_DEBUG

enum { SWITCH_DEFAULT_VIOLATION = 0 };

void valid_linked_aux( const char *text, refalrts::Iter i ) {
  printf("checking %s\n", text);
  if( 0 == i ) {
    return;
  }

  if( i->next ) {
    assert( i->next->prev == i );
  }

  if( i->prev ) {
    assert( i->prev->next == i );
  }
}

//==============================================================================
// ����������� ��������
//==============================================================================

// �������� �������������

void refalrts::use( refalrts::Iter& ) {
  /* ������ �� ������. ��� ������� �����������, ����� �������� ��������������
  ����������� � ���, ��� ���������� �� ������������ */;
}

void refalrts::use_counter( unsigned& ) {
  /* ������ �� ������. ��� ������� �����������, ����� �������� ��������������
  ����������� � ���, ��� ���������� �� ������������ */;
}

namespace {

refalrts::Iter next( refalrts::Iter current ) {
  return current->next;
}

refalrts::Iter prev( refalrts::Iter current ) {
  return current->prev;
}

bool is_open_bracket( refalrts::Iter node ) {
  return (refalrts::cDataOpenBracket == node->tag)
    || (refalrts::cDataOpenADT == node->tag);
}

bool is_close_bracket( refalrts::Iter node ) {
  return (refalrts::cDataCloseBracket == node->tag)
    || (refalrts::cDataCloseADT == node->tag);
}

} // unnamed namespace

void refalrts::move_left(
  refalrts::Iter& first, refalrts::Iter& last
) {
  //assert( (first == 0) == (last == 0) );
  if( first == 0 ) assert (last == 0);
  if( first != 0 ) assert (last != 0);

  if( first == last ) {
    first = 0;
    last = 0;
  } else {
    first = next( first );
  }
}

void refalrts::move_right(
  refalrts::Iter& first, refalrts::Iter& last
) {
  //assert( (first == 0) == (last == 0) );
  if( first == 0 ) assert (last == 0);
  if( first != 0 ) assert (last != 0);

  if( first == last ) {
    first = 0;
    last = 0;
  } else {
    last = prev( last );
  }
}

bool refalrts::empty_seq( refalrts::Iter first, refalrts::Iter last ) {
  //assert( (first == 0) == (last == 0) );
  if( first == 0 ) assert (last == 0);
  if( first != 0 ) assert (last != 0);

  return (first == 0) && (last == 0);
}

bool refalrts::function_left(
  refalrts::RefalFunctionPtr fn, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if( first->tag != cDataFunction ) {
    return false;
  } else if ( first->function_info.ptr != fn ) {
    return false;
  } else {
    move_left( first, last );
    return true;
  }
}

bool refalrts::function_right(
  refalrts::RefalFunctionPtr fn, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataFunction != last->tag ) {
    return false;
  } else if ( last->function_info.ptr != fn ) {
    return false;
  } else {
    move_right( first, last );
    return true;
  }
}

bool refalrts::char_left(
  char ch, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataChar != first->tag ) {
    return false;
  } else if ( first->char_info != ch ) {
    return false;
  } else {
    move_left( first, last );
    return true;
  }
}

bool refalrts::char_right(
  char ch, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataChar != last->tag ) {
    return false;
  } else if ( last->char_info != ch ) {
    return false;
  } else {
    move_right( first, last );
    return true;
  }
}


bool refalrts::number_left(
  refalrts::RefalNumber num, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataNumber != first->tag ) {
    return false;
  } else if ( first->number_info != num ) {
    return false;
  } else {
    move_left( first, last );
    return true;
  }
}

bool refalrts::number_right(
  refalrts::RefalNumber num, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataNumber != last->tag ) {
    return false;
  } else if ( last->number_info != num ) {
    return false;
  } else {
    move_right( first, last );
    return true;
  }
}

bool refalrts::ident_left(
  refalrts::RefalIdentifier ident, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataIdentifier != first->tag ) {
    return false;
  } else if ( first->ident_info != ident ) {
    return false;
  } else {
    move_left( first, last );
    return true;
  }
}

bool refalrts::ident_right(
  refalrts::RefalIdentifier ident, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataIdentifier != last->tag ) {
    return false;
  } else if ( last->ident_info != ident ) {
    return false;
  } else {
    move_right( first, last );
    return true;
  }
}

bool refalrts::brackets_left(
  refalrts::Iter& res_first, refalrts::Iter& res_last,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataOpenBracket != first->tag ) {
    return false;
  } else {
    refalrts::Iter left_bracket = first;
    refalrts::Iter right_bracket = left_bracket->link_info;

    if( next( left_bracket ) != right_bracket ) {
      res_first = next( left_bracket );
      res_last = prev( right_bracket );
    } else {
      res_first = 0;
      res_last = 0;
    }

    if( right_bracket == last ) {
      first = 0;
      last = 0;
    } else {
      first = next( right_bracket );
    }

    return true;
  }
}

bool refalrts::brackets_right(
  refalrts::Iter& res_first, refalrts::Iter& res_last,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if( cDataCloseBracket != last->tag ) {
    return false;
  } else {
    refalrts::Iter right_bracket = last;
    refalrts::Iter left_bracket = right_bracket->link_info;

    if( next( left_bracket ) != right_bracket ) {
      res_first = next( left_bracket );
      res_last = prev( right_bracket );
    } else {
      res_first = 0;
      res_last = 0;
    }

    if( first == left_bracket ) {
      first = 0;
      last = 0;
    } else {
      last = prev( left_bracket );
    }

    return true;
  }
}

bool refalrts::adt_left(
  refalrts::Iter& res_first, refalrts::Iter& res_last,
  refalrts::RefalFunctionPtr tag,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( cDataOpenADT != first->tag ) {
    return false;
  } else {
    refalrts::Iter left_bracket = first;
    refalrts::Iter right_bracket = left_bracket->link_info;
    refalrts::Iter pnext = next( left_bracket );

    if( pnext == right_bracket ) {
      return false;
    } else if( cDataFunction != pnext->tag ) {
      return false;
    } else if( pnext->function_info.ptr != tag ) {
      return false;
    } else {
      if( next( pnext ) != right_bracket ) {
        res_first = next( pnext );
        res_last = prev( right_bracket );
      } else {
        res_first = 0;
        res_last = 0;
      }

      if( right_bracket == last ) {
        first = 0;
        last = 0;
      } else {
        first = next( right_bracket );
      }

      return true;
    }
  }
}

bool refalrts::adt_right(
  refalrts::Iter& res_first, refalrts::Iter& res_last,
  refalrts::RefalFunctionPtr tag,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if( cDataCloseADT != last->tag ) {
    return false;
  } else {
    refalrts::Iter right_bracket = last;
    refalrts::Iter left_bracket = right_bracket->link_info;
    refalrts::Iter pnext = next( left_bracket );

    if( pnext == right_bracket ) {
      return false;
    } else if( cDataFunction != pnext->tag ) {
      return false;
    } else if( pnext->function_info.ptr != tag ) {
      return false;
    } else {
      if( next( pnext ) != right_bracket ) {
        res_first = next( pnext );
        res_last = prev( right_bracket );
      } else {
        res_first = 0;
        res_last = 0;
      }

      if( first == left_bracket ) {
        first = 0;
        last = 0;
      } else {
        last = prev( left_bracket );
      }

      return true;
    }
  }
}

bool refalrts::svar_left(
  refalrts::Iter& svar, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( is_open_bracket( first ) ) {
    return false;
  } else {
    svar = first;
    move_left( first, last );
    return true;
  }
}

bool refalrts::svar_right(
  refalrts::Iter& svar, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( is_close_bracket( last ) ) {
    return false;
  } else {
    svar = last;
    move_right( first, last );
    return true;
  }
}

bool refalrts::tvar_left(
  refalrts::Iter& tvar, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( is_open_bracket( first ) ) {
    refalrts::Iter right_bracket = first->link_info;

    tvar = first;
    first = right_bracket;
    move_left( first, last );
    return true;
  } else {
    tvar = first;
    move_left( first, last );
    return true;
  }
}

bool refalrts::tvar_right(
  refalrts::Iter& tvar, refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  if( empty_seq( first, last ) ) {
    return false;
  } else if ( is_close_bracket( last ) ) {
    refalrts::Iter right_bracket = last;
    refalrts::Iter left_bracket = right_bracket->link_info;

    tvar = left_bracket;
    last = left_bracket;
    move_right( first, last );
    return true;
  } else {
    tvar = last;
    move_right( first, last );
    return true;
  }
}

bool refalrts::next_term(
  refalrts::Iter& first, refalrts::Iter& last
) {
  /*
    ������� ������������ ��� �������� � ���������� ����� ��� �������
    �������� e-����������. �.�. �� ����� � ��������� ����� ����������� ����,
    ��� first != last, ������������ �������� ������� ����� �� ���������.
  */
  refalrts::Iter temp;
  return tvar_left( temp, first, last );
}

namespace refalrts {

class UnexpectedTypeException { };

} // namespace refalrts

namespace {

bool equal_nodes(
  refalrts::Iter node1, refalrts::Iter node2
) // throws refalrts::UnexpectedTypeException
{
  if( node1->tag != node2->tag ) {
    return false;
  } else {
    switch( node1->tag ) {
      case refalrts::cDataChar:
        return (node1->char_info == node2->char_info);
        // break;

      case refalrts::cDataNumber:
        return (node1->number_info == node2->number_info);
        // break;

      case refalrts::cDataFunction:
        return (node1->function_info.ptr == node2->function_info.ptr);
        // break;

      case refalrts::cDataIdentifier:
        return (node1->ident_info == node2->ident_info);
        // break;

      /*
        �������� � ������ ����� �������� ����� ��� ������ �����, �����
        �� ��� ����� ������ �� ������������� ���������.
      */
      case refalrts::cDataOpenBracket:
      case refalrts::cDataCloseBracket:
      case refalrts::cDataOpenADT:
      case refalrts::cDataCloseADT:
        return true;
        // break;

      case refalrts::cDataFile:
        return (node1->file_info == node2->file_info);
        // break;

      case refalrts::cDataClosure:
        return (node1->link_info == node2->link_info);
        // break;

      /*
        ������ ������� ������������� ������ ��� ������������� ��������� ���-
        ���������� �������. ������� ������ ����� �� ��� �� �������.
      */
      default:
        assert( SWITCH_DEFAULT_VIOLATION );
        throw refalrts::UnexpectedTypeException();
        // break;
    }
    // ��� ����� � case ����������� ���� return, ���� throw.
  }
}

bool equal_expressions(
  refalrts::Iter first1, refalrts::Iter last1,
  refalrts::Iter first2, refalrts::Iter last2
) // throws refalrts::UnexpectedTypeException
{
  assert( (first1 == 0) == (last1 == 0) );
  assert( (first2 == 0) == (last2 == 0) );

  for(
    /* ���������� ����������� �������, ������������� �� ����� */;
    // ������� ������� �����
    !empty_seq( first1, last1 ) && ! empty_seq( first2, last2 )
      && equal_nodes( first1, first2 );
    move_left( first1, last1 ), move_left( first2, last2 )
  ) {
    continue;
  }

  /*
    ����� empty_seq( first1, last1 ) || empty_seq( first2, last2 )
      || !equal_nodes( first1, first2 )
  */

  // �������� ���������� -- ���� �� �������� ����� � ����� ����������
  if( empty_seq( first1, last1 ) && empty_seq( first2, last2 ) ) {
    return true;
  } else {
    // ����� ������ ���������� ����� ��������������� � ������������
    return false;
  }
}

} // unnamed namespace

bool refalrts::repeated_stvar_left(
  refalrts::Iter& stvar, refalrts::Iter stvar_sample,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  refalrts::Iter left_term = 0;
  refalrts::Iter copy_last = last;

  if( tvar_left( left_term, first, last ) ) {
    refalrts::Iter left_term_e;
    refalrts::Iter stvar_sample_e;

    if( empty_seq( first, last ) ) {
      left_term_e = copy_last;
    } else {
      left_term_e = prev( first );
    }

    if( is_open_bracket( stvar_sample ) ) {
      stvar_sample_e = stvar_sample->link_info;
    } else {
      stvar_sample_e = stvar_sample;
    }

    bool equal = equal_expressions(
      left_term, left_term_e,
      stvar_sample, stvar_sample_e
    );

    if( equal ) {
      stvar = left_term;

      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool refalrts::repeated_stvar_right(
  refalrts::Iter& stvar, refalrts::Iter stvar_sample,
  refalrts::Iter& first, refalrts::Iter& last
) {
  assert( (first == 0) == (last == 0) );

  refalrts::Iter right_term = 0;
  refalrts::Iter old_last = last;

  if( tvar_right( right_term, first, last ) ) {
    refalrts::Iter right_term_e = old_last;
    refalrts::Iter stvar_sample_e;

    if( is_open_bracket( stvar_sample ) ) {
      stvar_sample_e = stvar_sample->link_info;
    } else {
      stvar_sample_e = stvar_sample;
    }

    bool equal = equal_expressions(
      right_term, right_term_e,
      stvar_sample, stvar_sample_e
    );

    if( equal ) {
      stvar = right_term;

      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool refalrts::repeated_evar_left(
  refalrts::Iter& evar_b, refalrts::Iter& evar_e,
  refalrts::Iter evar_b_sample, refalrts::Iter evar_e_sample,
  refalrts::Iter& first, refalrts::Iter& last
) {
  refalrts::Iter current = first;
  refalrts::Iter cur_sample = evar_b_sample;
  refalrts::Iter copy_last = last;

  for(
    /* ������������� ���� */;
    // ������� ������� �����
    !empty_seq( current, copy_last )
      && !empty_seq( cur_sample, evar_e_sample )
      && equal_nodes( current, cur_sample );
    move_left( cur_sample, evar_e_sample ), move_left( current, copy_last )
  ) {
    continue;
  }

  /*
    ����� empty_seq( current, copy_last )
      || empty_seq( cur_sample, evar_e_sample
      || ! equal_nodes( current, cur_sample )
  */
  if( empty_seq( cur_sample, evar_e_sample ) ) {
    // ��� ���������� ���������� ����� -- ��� ���������� ���������� ���������

    if( empty_seq( current, copy_last ) ) {
      evar_b = first;
      evar_e = last;

      first = 0;
      last = 0;
    } else {
      evar_b = first;
      evar_e = prev( current );

      first = current;
    }

    return true;
  } else {
    return false;
  }
}

bool refalrts::repeated_evar_right(
  refalrts::Iter& evar_b, refalrts::Iter& evar_e,
  refalrts::Iter evar_b_sample, refalrts::Iter evar_e_sample,
  refalrts::Iter& first, refalrts::Iter& last
) {
  refalrts::Iter current = last;
  refalrts::Iter cur_sample = evar_e_sample;
  refalrts::Iter copy_first = first;

  for(
    /* ������������� ���� */;
    // ������� ������������ ������� �����
    !empty_seq( copy_first, current )
      && !empty_seq( evar_b_sample, cur_sample )
      && equal_nodes( current, cur_sample );
    move_right( copy_first, current ), move_right( evar_b_sample, cur_sample )
  ) {
    continue;
  }

  /*
    ����� empty_seq( copy_first, current )
      || empty_seq( evar_b_sample, cur_sample )
      || ! equal_nodes( current, cur_sample )
  */

  if( empty_seq( evar_b_sample, cur_sample ) ) {
    // ��� ���������� ���������� �����: ��� ����������-������� �����������

    if( empty_seq( copy_first, current ) ) {
      evar_b = first;
      evar_e = last;

      first = 0;
      last = 0;
    } else {
      evar_b = next( current );
      evar_e = last;

      last = current;
    }

    return true;
  } else {
    return false;
  }
}

unsigned refalrts::read_chars(
  char buffer[], unsigned buflen, refalrts::Iter& first, refalrts::Iter& last
) {
  unsigned read = 0;
  for( ; ; ) {
    if( read == buflen ) {
      return read;
    } else if( empty_seq(first, last) ) {
      return read;
    } else if( first->tag != refalrts::cDataChar ) {
      return read;
    } else {
      buffer[read] = first->char_info;
      ++ read;
      move_left( first, last );
    }
  }
}

//------------------------------------------------------------------------------

// �������� �������������� ������

namespace refalrts{

namespace allocator {

void reset_allocator();
bool alloc_node( Iter& node );
Iter free_ptr();
void splice_to_freelist( Iter begin, Iter end );
void splice_from_freelist( Iter pos );

} // namespace allocator

} // namespace refalrts

//------------------------------------------------------------------------------

// �������� ��������������

namespace refalrts {

namespace profiler {

extern void start_building_result();

} // namespace profiler

} // namespace refalrts

//------------------------------------------------------------------------------

// �������� ���������� ����������

void refalrts::reset_allocator() {
  profiler::start_building_result();
  allocator::reset_allocator();
}

namespace {

bool copy_node( refalrts::Iter& res, refalrts::Iter sample ) {
  switch( sample->tag ) {
    case refalrts::cDataChar:
      return refalrts::alloc_char( res, sample->char_info );
      // break;

    case refalrts::cDataNumber:
      return refalrts::alloc_number( res, sample->number_info );
      // break;

    case refalrts::cDataFunction:
      return refalrts::alloc_name(
        res, sample->function_info.ptr, sample->function_info.name
      );
      // break;

    case refalrts::cDataIdentifier:
      return refalrts::alloc_ident( res, sample->ident_info );
      //break;

    case refalrts::cDataOpenBracket:
      return refalrts::alloc_open_bracket( res );
      // break;

    case refalrts::cDataCloseBracket:
      return refalrts::alloc_close_bracket( res );
      // break;

    case refalrts::cDataOpenADT:
      return refalrts::alloc_open_adt( res );
      // break;

    case refalrts::cDataCloseADT:
      return refalrts::alloc_close_adt( res );
      // break;

    case refalrts::cDataClosure: {
      bool allocated = refalrts::allocator::alloc_node( res );
      if( allocated ) {
        res->tag = refalrts::cDataClosure;
        refalrts::Iter head = sample->link_info;
        res->link_info = head;
        ++ (head->number_info);
        return true;
      } else {
        return false;
      }
    }
    // break;

    case refalrts::cDataFile: {
      bool allocated = refalrts::allocator::alloc_node( res );
      if( allocated ) {
        res->tag = refalrts::cDataFile;
        res->file_info = sample->file_info;
        return true;
      } else {
        return false;
      }
    }
    // break;

    /*
      �������� ������ ��������� ��������� -- ������� ������� �������
      ���� �� ������.
    */
    default:
      assert( SWITCH_DEFAULT_VIOLATION );
      throw refalrts::UnexpectedTypeException();
      // break;
  }
}

} // unnamed namespace


namespace refalrts {

namespace vm {

void make_dump( refalrts::Iter begin, refalrts::Iter end );

} // namespace vm

} // namespace refalrts

namespace {

bool copy_nonempty_evar(
  refalrts::Iter& evar_res_b, refalrts::Iter& evar_res_e,
  refalrts::Iter evar_b_sample, refalrts::Iter evar_e_sample
) {
  refalrts::Iter res = 0;
  refalrts::Iter bracket_stack = 0;

  refalrts::Iter prev_res_begin =
    prev( refalrts::allocator::free_ptr() );

  while( ! empty_seq( evar_b_sample, evar_e_sample ) ) {
    if( ! copy_node( res, evar_b_sample ) ) {
      return false;
    }

    if( is_open_bracket( res ) ) {
      res->link_info = bracket_stack;
      bracket_stack = res;
    } else if( is_close_bracket( res ) ) {
      assert( bracket_stack != 0 );

      refalrts::Iter open_cobracket = bracket_stack;
      bracket_stack = bracket_stack->link_info;
      link_brackets( open_cobracket, res );
    }

    move_left( evar_b_sample, evar_e_sample );
  }

  assert( bracket_stack == 0 );

  evar_res_b = next( prev_res_begin );
  evar_res_e = res;
  return true;
}

} // unnamed namespace

bool refalrts::copy_evar(
  refalrts::Iter& evar_res_b, refalrts::Iter& evar_res_e,
  refalrts::Iter evar_b_sample, refalrts::Iter evar_e_sample
) {
  if( empty_seq( evar_b_sample, evar_e_sample ) ) {
    evar_res_b = 0;
    evar_res_e = 0;
    return true;
  } else {
    return copy_nonempty_evar(
      evar_res_b, evar_res_e, evar_b_sample, evar_e_sample
    );
  }
}

bool refalrts::copy_stvar(
  refalrts::Iter& stvar_res, refalrts::Iter stvar_sample
) {
  refalrts::Iter end_of_sample;
  if( is_open_bracket( stvar_sample ) ) {
    end_of_sample = stvar_sample->link_info;
  } else {
    end_of_sample = stvar_sample;
  }

  refalrts::Iter end_of_res;
  return copy_evar(
    stvar_res, end_of_res, stvar_sample, end_of_sample
  );
}

bool refalrts::alloc_copy_evar(
  refalrts::Iter& res,
  refalrts::Iter evar_b_sample, refalrts::Iter evar_e_sample
) {
  if( empty_seq( evar_b_sample, evar_e_sample ) ) {
    res = 0;
    return true;
  } else {
    refalrts::Iter res_e = 0;
    return copy_nonempty_evar(
      res, res_e, evar_b_sample, evar_e_sample
    );
  }
}

bool refalrts::alloc_copy_svar_(
  refalrts::Iter& svar_res, refalrts::Iter svar_sample
) {
  return copy_node( svar_res, svar_sample );
}


bool refalrts::alloc_char( refalrts::Iter& res, char ch ) {
  if( allocator::alloc_node( res ) ) {
    res->tag = cDataChar;
    res->char_info = ch;
    return true;
  } else {
    return false;
  }
}

bool refalrts::alloc_number(
  refalrts::Iter& res, refalrts::RefalNumber num
) {
  if( allocator::alloc_node( res ) ) {
    res->tag = cDataNumber;
    res->number_info = num;
    return true;
  } else {
    return false;
  }
}

#ifdef MODULE_REFAL
const char *unknown() { return "@unknown"; }
#else
const char *unknown = "@unknown";
#endif

bool refalrts::alloc_name(
  refalrts::Iter& res,
  refalrts::RefalFunctionPtr fn,
  refalrts::RefalFuncName name
) {
  if( allocator::alloc_node( res ) ) {
    res->tag = cDataFunction;
    res->function_info.ptr = fn;
    if( name != 0 ) {
      res->function_info.name = name;
    } else {
      res->function_info.name = unknown;
    }
    return true;
  } else {
    return false;
  }
}

bool refalrts::alloc_ident(
  refalrts::Iter& res, refalrts::RefalIdentifier ident
) {
  if( allocator::alloc_node( res ) ) {
    res->tag = cDataIdentifier;
    res->ident_info = ident;
    return true;
  } else {
    return false;
  }
}

namespace {

bool alloc_some_bracket( refalrts::Iter& res, refalrts::DataTag tag ) {
  if( refalrts::allocator::alloc_node( res ) ) {
    res->tag = tag;
    return true;
  } else {
    return false;
  }
}

void link_adjacent( refalrts::Iter left, refalrts::Iter right ) {
  if( left != 0 ) {
    left->next = right;
  }

  if( right != 0 ) {
    right->prev = left;
  }
}

bool alloc_closure( refalrts::Iter& res ) {
  bool allocated = refalrts::allocator::alloc_node( res );
  if( allocated ) {
    refalrts::Iter head = 0;
    allocated = refalrts::allocator::alloc_node( head );
    if( allocated ) {
      refalrts::Iter prev_head = prev( head );
      refalrts::Iter next_head = next( head );

      link_adjacent( prev_head, next_head );
      link_adjacent( head, head );

      res->tag = refalrts::cDataClosure;
      res->link_info = head;

      head->tag = refalrts::cDataClosureHead;
      head->number_info = 1;

      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

} // unnamed namespace

bool refalrts::alloc_open_adt( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataOpenADT );
}

bool refalrts::alloc_close_adt( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataCloseADT );
}

bool refalrts::alloc_open_bracket( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataOpenBracket );
}

bool refalrts::alloc_close_bracket( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataCloseBracket );
}

bool refalrts::alloc_open_call( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataOpenCall );
}

bool refalrts::alloc_close_call( refalrts::Iter& res ) {
  return alloc_some_bracket( res, cDataCloseCall );
}

bool refalrts::alloc_chars(
  refalrts::Iter& res_b, refalrts::Iter& res_e,
  const char buffer[], unsigned buflen
) {
  if( buflen == 0 ) {
    res_b = 0;
    res_e = 0;
    return true;
  } else {
    refalrts::Iter before_begin_seq = prev( refalrts::allocator::free_ptr() );
    refalrts::Iter end_seq = 0;

    for( unsigned i = 0; i < buflen; ++ i ) {
      if( ! alloc_char( end_seq, buffer[i] ) ) {
        return false;
      }
    }

    res_b = next( before_begin_seq );
    res_e = end_seq;

    return true;
  }
}

bool refalrts::alloc_string(
  refalrts::Iter& res_b, refalrts::Iter& res_e, const char *string
) {
  if( *string == '\0' ) {
    res_b = 0;
    res_e = 0;
    return true;
  } else {
    refalrts::Iter before_begin_seq = prev( refalrts::allocator::free_ptr() );
    refalrts::Iter end_seq = 0;

    for( const char *p = string; *p != '\0'; ++ p ) {
      if( ! alloc_char( end_seq, *p ) ) {
        return false;
      }
    }

    res_b = next( before_begin_seq );
    res_e = end_seq;

    return true;
  }
}

namespace refalrts {

namespace vm {

void push_stack( refalrts::Iter call_bracket );

} // namespace vm

} // namespace refalrts

void refalrts::push_stack( Iter call_bracket ) {
  vm::push_stack( call_bracket );
}

void refalrts::link_brackets( Iter left, Iter right ) {
  left->link_info = right;
  right->link_info = left;
}

namespace {

refalrts::Iter list_splice(
  refalrts::Iter res, refalrts::Iter begin, refalrts::Iter end
) {

  VALID_LINKED( res );
  VALID_LINKED( res->prev );
  VALID_LINKED( begin );
  VALID_LINKED( begin->prev );
  VALID_LINKED( end );
  VALID_LINKED( end->prev );

  if( (res == begin) || empty_seq( begin, end ) ) {

    // ���� ���������� ���� �� ����
    return res;
  } else {
    refalrts::Iter prev_res = prev( res );
    refalrts::Iter prev_begin = prev( begin );
    refalrts::Iter next_end = next( end );

    link_adjacent( prev_res, begin );
    link_adjacent( end, res );
    link_adjacent( prev_begin, next_end );
  }

  VALID_LINKED( res );
  VALID_LINKED( res->prev );
  VALID_LINKED( begin );
  VALID_LINKED( begin->prev );
  VALID_LINKED( end );
  VALID_LINKED( end->next );

  return begin;
}

} // unnamed namespace

refalrts::Iter refalrts::splice_elem(
  refalrts::Iter res, refalrts::Iter elem
) {
  return list_splice( res, elem, elem );
}

refalrts::Iter refalrts::splice_stvar(
  refalrts::Iter res, refalrts::Iter var
) {
  refalrts::Iter var_end;
  if( is_open_bracket( var ) ) {
    var_end = var->link_info;
  } else {
    var_end = var;
  }

  return list_splice( res, var, var_end );
}

refalrts::Iter refalrts::splice_evar(
  refalrts::Iter res, refalrts::Iter begin, refalrts::Iter end
) {
  return list_splice( res, begin, end );
}

void refalrts::splice_to_freelist( refalrts::Iter begin, refalrts::Iter end ) {
  allocator::splice_to_freelist( begin, end );
}

void refalrts::splice_from_freelist( refalrts::Iter pos ) {
  allocator::splice_from_freelist( pos );
}

refalrts::FnResult refalrts::create_closure(
  refalrts::Iter begin, refalrts::Iter end
) {
  refalrts::Iter closure_b = begin;
  refalrts::Iter closure_e = end;

  refalrts::move_left( closure_b, closure_e ); // ������� <
  refalrts::move_left( closure_b, closure_e ); // ������� ����� �������
  refalrts::move_right( closure_b, closure_e ); // ������� >

  if( empty_seq( closure_b, closure_e ) )
    return refalrts::cRecognitionImpossible;

  refalrts::Iter closure = 0;

  if( ! alloc_closure( closure ) )
    return refalrts::cNoMemory;

  refalrts::Iter head = closure->link_info;

  list_splice( head, closure_b, closure_e );
  list_splice( begin, closure, closure );
  refalrts::splice_to_freelist( begin, end );

  return refalrts::cSuccess;
}

/*
  ���������� ��������� (������� + ��������) ������������ ���
  [next(head), prev(head)]. �.�. ��������� �������� ������ ��������
  create_closure, ������� ����������� ��������� ���������, ��
  next(head) != head, prev(head) != head.
*/

// ���������� ���������
refalrts::Iter refalrts::unwrap_closure( refalrts::Iter closure ) {
  assert( closure->tag == refalrts::cDataClosure );

  refalrts::Iter before_closure = prev( closure );
  refalrts::Iter head = closure->link_info;
  refalrts::Iter end_of_closure = prev( head );

  assert( head != prev( head ) );
  assert( head != next( head ) );

  link_adjacent( before_closure, head );
  link_adjacent( end_of_closure, closure );

  closure->tag = refalrts::cDataUnwrappedClosure;

  return prev(head);
}

// �������� ���������
refalrts::Iter refalrts::wrap_closure( refalrts::Iter closure ) {
  assert( closure->tag == refalrts::cDataUnwrappedClosure );

  refalrts::Iter head = closure->link_info;
  refalrts::Iter before_closure = prev( head );
  refalrts::Iter end_of_closure = prev( closure );

  assert( head != prev( head ) );
  assert( head != next( head ) );

  link_adjacent( before_closure, closure );
  link_adjacent( end_of_closure, head );

  closure->tag = refalrts::cDataClosure;

  return next(closure);
}

//------------------------------------------------------------------------------

// ������������� ��������� ���� ������������ �����

namespace refalrts {

namespace vm {

extern NodePtr g_left_swap_ptr;

} // namespace vm

} // namespace refalrts

refalrts::Iter refalrts::initialize_swap_head( refalrts::Iter head ) {
  assert( cDataFunction == head->tag );

  splice_elem( vm::g_left_swap_ptr, head );
  refalrts::RefalFuncName name = head->function_info.name;
  head->tag = cDataSwapHead;
  head->swap_info.next_head = vm::g_left_swap_ptr;
  head->swap_info.name = name;
  vm::g_left_swap_ptr = head;
  return vm::g_left_swap_ptr;
}

void refalrts::swap_info_bounds(
  refalrts::Iter& first, refalrts::Iter& last, refalrts::Iter head
) {
  assert( cDataSwapHead == head->tag );

  first = head;
  last = head->swap_info.next_head;
  move_left( first, last );
  move_right( first, last );
}

void refalrts::swap_save(
  refalrts::Iter head, refalrts::Iter first, refalrts::Iter last
) {
  assert( cDataSwapHead == head->tag );

  list_splice( head->swap_info.next_head, first, last );
}

//------------------------------------------------------------------------------

// �������� ��������������

namespace refalrts {

namespace profiler {

extern void start_generated_function();

} // namespace profiler

} // namespace refalrts

void refalrts::this_is_generated_function() {
  refalrts::profiler::start_generated_function();
}

//------------------------------------------------------------------------------

// ������ ��������

namespace refalrts {

namespace vm {

extern int g_ret_code;
extern void print_seq(FILE *output, refalrts::Iter begin, refalrts::Iter end);

} // namespace vm

} // namespace refalrts

void refalrts::set_return_code( int code ) {
  refalrts::vm::g_ret_code = code;
}

void refalrts::debug_print_expr(
  void *file, refalrts::Iter first, refalrts::Iter last
) {
  refalrts::vm::print_seq( static_cast<FILE*>(file), first, last );
}

//==============================================================================
// �������������� ������
//==============================================================================

namespace refalrts {

namespace allocator {

bool create_nodes();

void free_memory();

extern refalrts::Node g_last_marker;

refalrts::Node g_first_marker = { 0, & g_last_marker, refalrts::cDataIllegal };
refalrts::Node g_last_marker = { & g_first_marker, 0, refalrts::cDataIllegal };

const refalrts::NodePtr g_end_list = & g_last_marker;
refalrts::NodePtr g_free_ptr = & g_last_marker;

namespace pool {

enum { cChunkSize = 1000 };
typedef struct Chunk {
  Chunk *next;
  refalrts::Node elems[cChunkSize];
} Chunk;

typedef Chunk *ChunkPtr;

refalrts::NodePtr alloc_node();
void free();
bool grow();

ChunkPtr g_pool = 0;
unsigned g_avail = 0;
refalrts::Node *g_pnext_node = 0;

} // namespace pool

unsigned long g_memory_use = 0;

} // namespace allocator

} // namespace refalrts

inline void refalrts::allocator::reset_allocator() {
  g_free_ptr = g_first_marker.next;
}

bool refalrts::allocator::alloc_node( refalrts::Iter& node ) {
  if( (g_free_ptr == & g_last_marker) && ! create_nodes() ) {
    return false;
  } else {
    if( refalrts::cDataClosure == g_free_ptr->tag ) {
      refalrts::Iter head = g_free_ptr->link_info;
      -- head->number_info;

      if( 0 == head->number_info ) {
        unwrap_closure( g_free_ptr );
        // ������ ����� g_free_ptr ��������� "����������" ���������
        g_free_ptr->tag = refalrts::cDataClosureHead;
        g_free_ptr->number_info = 407193; // :-)

        g_free_ptr = head;
      }
    }

    node = g_free_ptr;
    g_free_ptr = next( g_free_ptr );
    node->tag = refalrts::cDataIllegal;
    return true;
  }
}

refalrts::Iter refalrts::allocator::free_ptr() {
  return g_free_ptr;
}

void refalrts::allocator::splice_to_freelist(
  refalrts::Iter begin, refalrts::Iter end
) {
  reset_allocator();
  g_free_ptr = list_splice( g_free_ptr, begin, end );
}

void refalrts::allocator::splice_from_freelist( refalrts::Iter pos ) {
  if (g_free_ptr != g_first_marker.next ) {
    list_splice( pos, g_first_marker.next, g_free_ptr->prev );
  }
}

bool refalrts::allocator::create_nodes() {
  refalrts::NodePtr new_node = refalrts::allocator::pool::alloc_node();

#ifdef MEMORY_LIMIT

  if( g_memory_use >= MEMORY_LIMIT ) {
    return false;
  }

#endif //ifdef MEMORY_LIMIT

  if( new_node == 0 ) {
    return false;
  } else {
    refalrts::NodePtr before_free_ptr = prev( g_free_ptr );
    before_free_ptr->next = new_node;
    new_node->prev = before_free_ptr;

    g_free_ptr->prev = new_node;
    new_node->next = g_free_ptr;

    g_free_ptr = new_node;
    g_free_ptr->tag = refalrts::cDataIllegal;
    ++ g_memory_use;

    return true;
  }
}

void refalrts::allocator::free_memory() {
  refalrts::allocator::pool::free();
#ifndef DONT_PRINT_STATISTICS
  fprintf(
    stderr,
    "Memory used %lu nodes, %lu * %lu = %lu bytes\n",
    g_memory_use,
    g_memory_use,
    static_cast<unsigned long>(sizeof(Node)),
    static_cast<unsigned long>(g_memory_use * sizeof(Node))
  );
#endif // DONT_PRINT_STATISTICS
}

refalrts::NodePtr refalrts::allocator::pool::alloc_node() {
  if( (g_avail != 0) || grow() ) {
    -- g_avail;
    return g_pnext_node++;
  } else {
    return 0;
  }
}

bool refalrts::allocator::pool::grow() {
  ChunkPtr p = static_cast<ChunkPtr>( malloc( sizeof(Chunk) ) );
  if( p != 0 ) {
    p->next = g_pool;
    g_pool = p;
    g_avail = cChunkSize;
    g_pnext_node = p->elems;
    return true;
  } else {
    return false;
  }
}

void refalrts::allocator::pool::free() {
  while( g_pool != 0 ) {
    ChunkPtr p = g_pool;
    g_pool = g_pool->next;
    ::free( p );
  }
}

//==============================================================================
// ���������� �������������
//==============================================================================

namespace refalrts {

namespace profiler {

clock_t g_start_program_time;
clock_t g_start_pattern_match_time;
clock_t g_total_pattern_match_time;
clock_t g_start_building_result_time;
clock_t g_total_building_result_time;

bool g_in_generated;

void start_profiler();
void end_profiler();
void start_generated_function();
void after_step();

} // namespace profiler

} // namespace refalrts

void refalrts::profiler::start_profiler() {
  g_start_program_time = clock();
  g_in_generated = false;
}

void refalrts::profiler::end_profiler() {
  refalrts::profiler::after_step();
#ifndef DONT_PRINT_STATISTICS

  const double cfCLOCKS_PER_SEC = (double) CLOCKS_PER_SEC;

  double full_time =
    (clock() - g_start_program_time) / cfCLOCKS_PER_SEC;
  double pattern_time = g_total_pattern_match_time / cfCLOCKS_PER_SEC;
  double result_time = g_total_building_result_time / cfCLOCKS_PER_SEC;
  double refal_time = pattern_time + result_time;
  double io_time = full_time - refal_time;

  double pattern_percent = 100 * pattern_time / refal_time;
  double pattern_clear_percent = 100 * pattern_time / full_time;
  double result_percent = 100 * result_time / refal_time;
  double result_clear_percent = 100 * result_time / full_time;
  double refal_persent = 100 * refal_time / full_time;

  fprintf(stderr, "\nTotal program time: %.3f seconds.\n", full_time);
  fprintf(
    stderr,
    "Pattern match time: %.3f seconds (%1.1f%%, %1.1f%%), "
    "p/r = %.2f.\n", pattern_time, pattern_percent,
    pattern_clear_percent, pattern_time / result_time
  );
  fprintf(
    stderr,
    "Building result time: %.3f seconds (%1.1f%%, %1.1f%%), "
    "r/p = %.2f.\n", result_time, result_percent,
    result_clear_percent, result_time / pattern_time
  );
  fprintf(
    stderr, "Total refal time: %.3f seconds (%1.1f%%).\n",
    refal_time, refal_persent
  );
  fprintf(
    stderr, "Builtin time: %.3f seconds (%1.1f%%).\n",
    io_time, 100.0 - refal_persent
  );
#endif // DONT_PRINT_STATISTICS
}

void refalrts::profiler::start_generated_function() {
  g_start_pattern_match_time = clock();
  g_in_generated = true;
}

void refalrts::profiler::start_building_result() {
  if( g_in_generated ) {
    g_start_building_result_time = clock();
    clock_t pattern_match =
      g_start_building_result_time - g_start_pattern_match_time;
    g_total_pattern_match_time += pattern_match;
  }
}

void refalrts::profiler::after_step() {
  if( g_in_generated ) {
    clock_t building_result = clock() - g_start_building_result_time;
    g_total_building_result_time += building_result;
  }

  g_in_generated = false;
}

//==============================================================================
// ����������� ������
//==============================================================================

#ifdef MODULE_REFAL
#define GO_START_FUNCTION Entry_Go
#else
#define GO_START_FUNCTION Go
#endif

extern refalrts::FnResult GO_START_FUNCTION(
  refalrts::Iter, refalrts::Iter
);

namespace refalrts {

namespace vm {

void push_stack( refalrts::Iter call_bracket );
refalrts::Iter pop_stack();
bool empty_stack();

bool init_view_field();

refalrts::FnResult main_loop();
refalrts::FnResult execute_active( refalrts::Iter begin, refalrts::Iter end );
void make_dump( refalrts::Iter begin, refalrts::Iter end );
FILE* dump_stream();

void free_view_field();

refalrts::NodePtr g_stack_ptr = 0;

extern refalrts::Node g_last_marker;

refalrts::Node g_first_marker = { 0, & g_last_marker, refalrts::cDataIllegal };
refalrts::Node g_last_marker = { & g_first_marker, 0, refalrts::cDataIllegal };

refalrts::Iter g_begin_view_field = & g_last_marker;
const refalrts::Iter g_end_view_field = & g_last_marker;

refalrts::NodePtr g_left_swap_ptr = g_end_view_field;

unsigned g_step_counter = 0;

int g_ret_code;

} // namespace vm

} // namespace refalrts

void refalrts::vm::push_stack( refalrts::Iter call_bracket ) {
  call_bracket->link_info = g_stack_ptr;
  g_stack_ptr = call_bracket;
}

refalrts::Iter refalrts::vm::pop_stack() {
  refalrts::Iter res = g_stack_ptr;
  g_stack_ptr = g_stack_ptr->link_info;
  return res;
}

bool refalrts::vm::empty_stack() {
  return (g_stack_ptr == 0);
}

#ifdef MODULE_REFAL
//$LABEL Go
template <typename T>
struct GoL_ {
  static const char *name() {
    return "Go";
  }
};
#define GO_NAME GoL_<int>::name
#else
#define GO_NAME "Go"
#endif

bool refalrts::vm::init_view_field() {
  refalrts::reset_allocator();
  refalrts::Iter res = g_begin_view_field;
  refalrts::Iter n0 = 0;
  if( ! refalrts::alloc_open_call( n0 ) )
    return false;
  refalrts::Iter n1 = 0;
  if( ! refalrts::alloc_name( n1, & GO_START_FUNCTION, GO_NAME ) )
    return false;
  refalrts::Iter n2 = 0;
  if( ! refalrts::alloc_close_call( n2 ) )
    return false;
  refalrts::push_stack( n2 );
  refalrts::push_stack( n0 );
  res = refalrts::splice_elem( res, n2 );
  res = refalrts::splice_elem( res, n1 );
  res = refalrts::splice_elem( res, n0 );
  g_begin_view_field = res;

  return true;
}

refalrts::FnResult refalrts::vm::main_loop() {
  FnResult res = cSuccess;
  while( ! empty_stack() ) {
    refalrts::Iter active_begin = pop_stack();
    assert( ! empty_stack() );
    refalrts::Iter active_end = pop_stack();

    res = execute_active( active_begin, active_end );
    refalrts::profiler::after_step();

    ++ g_step_counter;

    if( res != cSuccess ) {
      switch( res ) {
        case refalrts::cRecognitionImpossible:
          fprintf(stderr, "\nRECOGNITION IMPOSSIBLE\n\n");
          break;

        case refalrts::cNoMemory:
          fprintf(stderr, "\nNO MEMORY\n\n");
          break;

        case refalrts::cExit:
          return res;

        default:
          fprintf(stderr, "\nUNKNOWN ERROR\n\n");
          break;
      }
      make_dump( active_begin, active_end );
      return res;
    } else {
      continue;
    }
  }

  // printf("\n\nTOTAL STEPS %d\n", g_step_counter);

  return res;
}

refalrts::FnResult refalrts::vm::execute_active(
  refalrts::Iter begin, refalrts::Iter end
) {

#if SHOW_DEBUG

  static unsigned s_counter = 0;

  ++s_counter;

  fprintf(stderr, "\nexecute %d\n", s_counter);
  if( s_counter > (unsigned) SHOW_DEBUG ) {
    fprintf(refalrts::vm::dump_stream(), "\nexecute %d\n", s_counter);
    make_dump( begin, end );
  }

#endif // SHOW_DEBUG

  refalrts::Iter function = next( begin );
  if( cDataFunction == function->tag ) {
    return (function->function_info.ptr)( begin, end );
  } else if( cDataClosure == function->tag ) {
    refalrts::Iter head = function->link_info;

    if( 1 == head->number_info ) {
      /*
        ���������� ���, ��� ��� �������� ���������� ��������� �����������
        � ���� ������ ����� ������� � (����������!) ����� ���������.
        �� ��������� �������, ��������� � ���������� ����������� ���������
        � ������ ��������� ������, ����������������� ��� ��� ������ ���������.
      */
      unwrap_closure( function );
      function->tag = cDataClosureHead;
      function->number_info = 73501505; // :-)
      splice_to_freelist( function, function );
      splice_to_freelist( head, head );
    } else {
      refalrts::Iter begin_argument = next( function );
      refalrts::Iter closure_b = 0;
      refalrts::Iter closure_e = 0;

      if( ! copy_evar( closure_b, closure_e, next(head), prev(head) ) )
        return cNoMemory;

      list_splice( begin_argument, closure_b, closure_e );
      splice_to_freelist( function, function );
    }

    refalrts::vm::push_stack( end );
    refalrts::vm::push_stack( begin );

    return cSuccess;
  } else {
    return cRecognitionImpossible;
  }
}

namespace {

void print_indent(FILE *output, unsigned level)
{
  enum { cPERIOD = 4 };
  putc( '\n', output );
  for( unsigned i = 0; i < level; ++i )
  {
    // ������ cPERIOD ������� ������ ������� ������ �����.
    bool put_marker = ((i % cPERIOD) == (cPERIOD - 1));

    const char cSpace =  ' ';
    const char cMarker = '.';

    putc( (put_marker ? cMarker : cSpace), output );
  }
}

} // unnamed namespace

void refalrts::vm::print_seq(
  FILE *output, refalrts::Iter begin, refalrts::Iter end
) {
  enum {
    cStateView = 100,
    cStateString,
    cStateFinish
  } state = cStateView;

  unsigned indent = 0;
  bool after_bracket = false;
  bool reset_after_bracket = true;

  while( (state != cStateFinish) && ! refalrts::empty_seq( begin, end ) ) {
    if( reset_after_bracket )
    {
      after_bracket = false;
      reset_after_bracket = false;
    }

    if( after_bracket )
    {
      reset_after_bracket = true;
    }

    switch( state ) {
      case cStateView:
        switch( begin->tag ) {
          case refalrts::cDataIllegal:
            if( 0 == begin->prev ) {
              fprintf( output, "[FIRST] " );
            } else if ( 0 == begin->next ) {
              fprintf( output, "\n[LAST]" );
              state = cStateFinish;
            } else {
              fprintf( output, "\n[NONE]" );
            }
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataSwapHead:
#ifdef MODULE_REFAL
            fprintf( output, "\n\n*Swap %s:\n", (begin->swap_info.name)() );
#else
            fprintf( output, "\n\n*Swap %s:\n", begin->swap_info.name );
#endif
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataChar:
            state = cStateString;
            fprintf( output, "\'" );
            continue;

          case refalrts::cDataNumber:
            fprintf( output, "%lu ", begin->number_info );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataFunction:
#ifdef MODULE_REFAL
            fprintf( output, "&%s ", (begin->function_info.name)() );
#else
            if( begin->function_info.name[0] != 0 ) {
              fprintf( output, "&%s ", begin->function_info.name );
            } else {
              fprintf( output, "&%p ", begin->function_info.ptr );
            }
#endif
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataIdentifier:
            fprintf( output, "#%s ", (begin->ident_info)() );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataOpenADT:
            if( ! after_bracket )
            {
              print_indent( output, indent );
            }
            ++indent;
            after_bracket = true;
            reset_after_bracket = false;
            fprintf( output, "[" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataCloseADT:
            --indent;
            fprintf( output, "]" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataOpenBracket:
            if( ! after_bracket )
            {
              print_indent( output, indent );
            }
            ++indent;
            after_bracket = true;
            reset_after_bracket = false;
            fprintf( output, "(" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataCloseBracket:
            --indent;
            fprintf( output, ")" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataOpenCall:
            if( ! after_bracket )
            {
              print_indent( output, indent );
            }
            ++indent;
            after_bracket = true;
            reset_after_bracket = false;
            fprintf( output, "<" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataCloseCall:
            --indent;
            fprintf( output, ">" );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataFile:
            fprintf( output, "*%p ", begin->file_info );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataClosure:
            fprintf( output, "{ " );
            begin = unwrap_closure( begin );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataClosureHead:
            fprintf( output, "[%lu] ", begin->number_info );
            refalrts::move_left( begin, end );
            continue;

          case refalrts::cDataUnwrappedClosure:
            fprintf( output, "} " );
            begin = wrap_closure( begin );
            continue;

          default:
            assert( SWITCH_DEFAULT_VIOLATION );
            throw refalrts::UnexpectedTypeException();
            // break;
        }

      case cStateString:
        switch( begin->tag ) {
          case refalrts::cDataChar: {
            unsigned char ch = static_cast<unsigned char>( begin->char_info );
            switch( ch )
              {
                case '(': case ')':
                case '<': case '>':
                  fprintf( output, "\\%c", ch );
                  break;

                case '\n':
                  fprintf( output, "\\n" );
                  break;

                case '\t':
                  fprintf( output, "\\t" );
                  break;

                case '\\':
                  fprintf( output, "\\\\" );
                  break;

                case '\'':
                  fprintf( output, "\\\'" );
                  break;

                default:
                  if( ch < '\x20' ) {
                    fprintf( output, "\\x%02x", static_cast<int>(ch) );
                  } else {
                    fprintf( output, "%c", ch );
                  }
                  break;
              }
              refalrts::move_left( begin, end );
              continue;
            }

          default:
            state = cStateView;
            fprintf( output, "\' " );
            continue;
        }

      case cStateFinish:
        continue;

      default:
        assert( SWITCH_DEFAULT_VIOLATION );
        throw refalrts::UnexpectedTypeException();
    }
  }

  if( cStateString == state ) {
    fprintf( output, "\'" );
  }
}

void refalrts::vm::make_dump( refalrts::Iter begin, refalrts::Iter end ) {
  using refalrts::vm::dump_stream;

  fprintf( dump_stream(), "\nERROR EXPRESSION:\n" );
  print_seq( dump_stream(), begin, end );
  fprintf( dump_stream(), "\nVIEW FIELD:\n" );
  print_seq( dump_stream(), & g_first_marker, & g_last_marker );

#ifdef DUMP_FREE_LIST

  fprintf( dump_stream(), "\nFREE LIST:\n" );
  print_seq(
    dump_stream(),
    & refalrts::allocator::g_first_marker,
    & refalrts::allocator::g_last_marker
  );

#endif //ifdef DUMP_FREE_LIST

  fprintf( dump_stream(),"\nEnd dump\n");
  fflush(dump_stream());
}

FILE *refalrts::vm::dump_stream() {
#ifdef DUMP_FILE

  static FILE *dump_file = 0;

  if( dump_file == 0 ) {
    // ���������� ������� ����.
    // ���� ���� �� �����������, ���������� stderr
    dump_file = fopen( DUMP_FILE, "wt" );

    if( dump_file == 0 ) {
      dump_file = stderr;
    }
  }

  return dump_file;

#else //ifdef DUMP_FILE

  return stderr;

#endif //ifdef DUMP_FILE
}

void refalrts::vm::free_view_field() {
  refalrts::Iter begin = g_first_marker.next;
  refalrts::Iter end = & g_last_marker;

  if( begin != end ) {
    end = end->prev;
    refalrts::allocator::splice_to_freelist( begin, end );
  } else {
    /*
      ���� ������ ������ -- ��� �� ����� �����������.
    */;
  }

#ifndef DONT_PRINT_STATISTICS
  fprintf( stderr, "Step count %d\n", g_step_counter );
#endif // DONT_PRINT_STATISTICS
}

//==============================================================================
// �������������
//==============================================================================

refalrts::FnResult refalrts::interpret_array(
  const refalrts::ResultAction raa[],
  refalrts::Iter allocs[],
  refalrts::Iter begin, refalrts::Iter end
) {
  int i = 0;
  Iter stack_ptr = 0;
  Iter res = begin;
  Iter cobracket;

  while(raa[i].cmd != icEnd)
  {
    //��������� ������
    switch(raa[i].cmd)
    {
      case icChar:
        if(!alloc_char(*allocs, static_cast<char>(raa[i].value)))
          return cNoMemory;
        ++allocs;
        break;

      case icInt:
        if(!alloc_number(*allocs, raa[i].value))
          return cNoMemory;
        ++allocs;
        break;

      case icFunc:
        if(
            !alloc_name(
              *allocs,
              (RefalFunctionPtr)(raa[i].ptr_value1),
              (RefalFuncName)(raa[i].ptr_value2)
            )
        )
          return cNoMemory;
        ++allocs;
        break;

      case icIdent:
        if(
            !alloc_ident(
              *allocs,
              (RefalIdentifier)(raa[i].ptr_value1)
            )
        )
          return cNoMemory;
        ++allocs;
        break;

      case icBracket:
        switch(raa[i].value)
        {
          case ibOpenADT:
            if(!alloc_open_adt(*allocs))
              return cNoMemory;
            (*allocs)->link_info = stack_ptr;
            stack_ptr = *allocs;
            ++allocs;
            break;

          case ibOpenBracket:
            if(!alloc_open_bracket(*allocs))
              return cNoMemory;
            (*allocs)->link_info = stack_ptr;
            stack_ptr = *allocs;
            ++allocs;
            break;

          case ibOpenCall:
            if(!alloc_open_call(*allocs))
              return cNoMemory;
            (*allocs)->link_info = stack_ptr;
            stack_ptr = *allocs;
            ++allocs;
            break;

          case ibCloseADT:
            if(!alloc_close_adt(*allocs))
              return cNoMemory;
            cobracket = stack_ptr;
            stack_ptr = stack_ptr->link_info;
            link_brackets( *allocs, cobracket );
            ++allocs;
            break;

          case ibCloseBracket:
            if(!alloc_close_bracket(*allocs))
              return cNoMemory;
            cobracket = stack_ptr;
            stack_ptr = stack_ptr->link_info;
            link_brackets( *allocs, cobracket );
            ++allocs;
            break;

          case ibCloseCall:
            if(!alloc_close_call(*allocs))
              return cNoMemory;
            cobracket = stack_ptr;
            stack_ptr = stack_ptr->link_info;
            link_brackets( *allocs, cobracket );
            ++allocs;
            break;

          default:
            throw UnexpectedTypeException();
        }

      case icSpliceSTVar:
        break;

      case icSpliceEVar:
        break;

      case icCopySTVar:
        if(!copy_stvar(*allocs, *static_cast<Iter*>(raa[i].ptr_value1)))
          return cNoMemory;
        ++allocs;
        break;

      case icCopyEVar: {
        refalrts::Iter& ebegin = *allocs;
        ++allocs;
        refalrts::Iter& eend = *allocs;
        ++allocs;
        if(
            !copy_evar(
              ebegin,
              eend,
              *static_cast<Iter*>(raa[i].ptr_value1),
              *static_cast<Iter*>(raa[i].ptr_value2)
            )
          )
          return cNoMemory;
        break;
      }

      default:
        throw UnexpectedTypeException();
    }
    i++;
  }

  while(i >= 0)
  {
    //���������� �����
    switch(raa[i].cmd)
    {
      case icChar:
      case icInt:
      case icFunc:
      case icIdent:
        --allocs;
        res = splice_elem(res, *allocs);
        break;

      case icSpliceSTVar:
        res = splice_stvar(res, *static_cast<Iter*>(raa[i].ptr_value1));
        break;

      case icSpliceEVar:
        res = splice_evar(res, *static_cast<Iter*>(raa[i].ptr_value1), *static_cast<Iter*>(raa[i].ptr_value2));
        break;

      case icBracket:
        --allocs;
        if( raa[i].value == ibCloseCall )
        {
          Iter open_call = (*allocs)->link_info;
          push_stack(*allocs);
          push_stack(open_call);
        }
        res = splice_elem( res, *allocs);
        break;

      case icCopyEVar: {
        --allocs;
        refalrts::Iter eend = *allocs;
        --allocs;
        refalrts::Iter ebegin = *allocs;
        res = splice_evar(res, ebegin, eend);
        break;
      }

      case icCopySTVar:
        --allocs;
        res = splice_stvar(res, *allocs);
        break;

      case icEnd:
        break;

      default:
        throw UnexpectedTypeException();
    }
    i--;
  }
  splice_to_freelist(begin, end);

  return cSuccess;
}

//==============================================================================

// ������������ � Library.cpp

char **g_argv = 0;
int g_argc = 0;

int main(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;

  refalrts::FnResult res;
  try {
    refalrts::vm::init_view_field();
    refalrts::profiler::start_profiler();
    res = refalrts::vm::main_loop();
    fflush(stderr);
    fflush(stdout);
  } catch ( refalrts::UnexpectedTypeException ) {
    fprintf(stderr, "INTERNAL ERROR: check all switches\n");
    return 3;
  } catch (...) {
    fprintf(stderr, "INTERNAL ERROR: unknown exception\n");
    return 4;
  }

  refalrts::profiler::end_profiler();
  refalrts::vm::free_view_field();
  refalrts::allocator::free_memory();

  fflush(stdout);

  switch( res ) {
    case refalrts::cSuccess:
      return 0;

    case refalrts::cRecognitionImpossible:
      return 1;

    case refalrts::cNoMemory:
      return 2;

    case refalrts::cExit:
      return refalrts::vm::g_ret_code;

    default:
      fprintf(stderr, "INTERNAL ERROR: check switch in main");
      return 5;
  }
}
