/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif
/* #include <gnome-xml/parser.h> */
#include <libxml/parser.h>	/* Ver.2.80 */
#include <string.h>

#ifndef	USE_LIB_GLADE
#	include "support.h"
#endif
#include "bjuidefs.h"


static char* g_keytext_dir = NULL;
static char* g_reverse_key;


static GTree* CreateTree()
{
	return g_tree_new((GCompareFunc)strcmp);
}

static gint TreeTraverseFunc(gpointer key, gpointer value, gpointer data)
{
	g_free((gchar*)key);
	g_free((gchar*)value);

	return FALSE;
}

static void FreeTree(GTree* tree)
{
	g_tree_foreach(tree, TreeTraverseFunc, NULL);
	g_tree_destroy(tree);
}

static void AddKeyAndTextToTree(xmlNodePtr xmlnode, GTree* tree)
{
	char *key, *text;

	if( !xmlnode->name || g_ascii_strcasecmp((const gchar *)xmlnode->name,"Item") != 0 )
		return;

	key  = g_strdup((const gchar *)xmlGetProp(xmlnode,(const xmlChar *)"key"));
	text = g_strdup((const gchar *)xmlNodeGetContent(xmlnode));

	if( key != NULL && text != NULL )
	{
		g_tree_insert(tree, (gpointer)key, (gpointer)text);
	}
}

static void ParseXMLDoc(xmlDocPtr doc, GTree* tree)
{
	xmlNodePtr node;

/*	for( node = doc->root->childs ; node != NULL ; node = node->next ) */
	for( node = doc->xmlRootNode->xmlChildrenNode ; node != NULL ; node = node->next )
	{
		AddKeyAndTextToTree(node, tree);
	}
}

static gboolean ReadXMLFile(char *fname, GTree* tree)
{
	xmlDocPtr doc;

	if( (doc = xmlParseFile(fname)) == NULL )
		return FALSE;

#if 0
	if( doc->root == NULL
	 || doc->root->name == NULL
	 || g_strcasecmp(doc->root->name, "KeyTextList") != 0)
	{
		xmlFreeDoc(doc);
		return FALSE;
	}
#endif
	if( doc->xmlRootNode == NULL
	 || doc->xmlRootNode->name == NULL
	 || g_ascii_strcasecmp((const gchar *)doc->xmlRootNode->name, "KeyTextList") != 0)
	{
		xmlFreeDoc(doc);
		return FALSE;
	}

	ParseXMLDoc(doc, tree);
	xmlFreeDoc(doc);

	return TRUE;
}

void SetKeyTextDir(gchar* dirname)
{
	if( g_keytext_dir != NULL )
		g_free(g_keytext_dir);

	g_keytext_dir = g_strdup(dirname);
}

KeyTextList* LoadKeyTextList(gchar* filename)
{
	KeyTextList* list;
	gchar* pathname = NULL;

	if( !g_keytext_dir || !filename )
		return NULL;

	if( (pathname = CheckFileExists(g_keytext_dir, filename)) == NULL )
		if( (pathname = CheckFileExists("keytext", filename)) == NULL )
			return NULL;

	list = (KeyTextList*)g_malloc(sizeof(KeyTextList));

	if( list != NULL )
	{
		if( (list->tree = CreateTree()) != NULL )
		{
			if( ReadXMLFile(pathname, list->tree) )
			{
				return list;
			}
			FreeTree(list->tree);
		}
		g_free(list);
	}
	return NULL;
}

void FreeKeyTextList(KeyTextList* list)
{
	FreeTree(list->tree);
	g_free(list);
}

static gint ReverseSearchFunc(gpointer key, gpointer value, gpointer data)
{
	if( strcmp((gchar*)value, (gchar*)data) == 0 )
	{
		g_reverse_key = key;
		return TRUE;
	}
	else
		return FALSE;
}

gchar* LookupText(KeyTextList* list, const gchar* key)
{
	if( list == NULL || list->tree == NULL || key == NULL )
		return NULL;

	return (gchar*)dgettext(PACKAGE,
					(gchar*)g_tree_lookup(list->tree, (gpointer)key));
}

gchar* LookupKey(KeyTextList* list, const gchar* text)
{
	if( list == NULL || list->tree == NULL || text == NULL )
		return NULL;

	g_reverse_key = NULL;
	g_tree_foreach(list->tree, ReverseSearchFunc, (gpointer)text);

	return g_reverse_key;
}

