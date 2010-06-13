// pte_set_flags and pte_clear_flags don't actually change any system
// structures, they only provide you with the modified copies of
// entries. set_pte is the function that modifies the structures

inline void set_present(pte_t* ptep)
  set_pte(ptep, pte_set_flags(*ptep, _PAGE_PRESENT));

inline void clear_present(pte_t* ptep)
  set_pte(ptep, pte_clear_flags(*ptep, _PAGE_PRESENT));

pte_t* virt_to_pte(unsigned int addr)
{
  // Not the most optimal code, but pretty illustrative
  pgd_t* pgd = pgd_offset_k(addr);
  pud_t* pud = pud_offset(pgd, addr);
  pmd_t* pmd = pmd_offset(pud, addr);
  return pte_offset(pmd, addr);
}
