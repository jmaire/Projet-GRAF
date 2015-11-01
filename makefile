# Répertoires
INCLUDEDIR =./INCLUDE
LIBDIR=./LIB
OBJDIR=./OBJ
SRCDIR=./SRC

#
CC=gcc
CFLAGS=-I$(INCLUDEDIR)

SL=ar rcs

#
LISTEOBJ=$(OBJDIR)/MaListe.o
GRAPHEOBJ=$(OBJDIR)/Graphe.o

# Cible proncipale
all: libliste libgraphe

# Règle de construction dee MaListe.a
libliste: $(LISTEOBJ) $(LIBDIR)
	$(SL) $(LIBDIR)/$@.a $<

# Règle de construction de Graphe.a
libgraphe: $(GRAPHEOBJ) $(LIBDIR)
	$(SL) $(LIBDIR)/$@.a $<

# Règle de construction de MaListe.o
$(LISTEOBJ) : $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/%.h $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction de Graphe.o
$(GRAPHEOBJ) : $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/%.h $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction des répertoires
$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

#
clean:
	rm $(OBJDIR)

veryclean: clean
	rm $(LIBDIR)
