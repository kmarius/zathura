/* See LICENSE file for license and copyright information */

#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include "page.h"
#include "document.h"
#include "version.h"

typedef struct zathura_document_functions_s zathura_document_functions_t;
typedef struct zathura_document_data_s zathura_document_data_t;
typedef struct zathura_page_data_s zathura_page_data_t;

/**
 * Functions register function
 *
 * @param functions The functions struct
 */
typedef void (*zathura_plugin_register_function_t)(zathura_document_functions_t* functions);

/**
 * Sets the functions register function of the plugin
 *
 * @param plugin The plugin
 */
void zathura_plugin_set_register_functions_function(zathura_plugin_t* plugin, zathura_plugin_register_function_t register_function);

/**
 * Sets the functions register function of the plugin
 *
 * @param plugin The plugin
 */
void zathura_plugin_add_mimetype(zathura_plugin_t* plugin, const char* mime_type);

/**
 * Register a plugin.
 *
 * @param plugin_name the name of the plugin
 * @param major the plugin's major version
 * @param minor the plugin's minor version
 * @param rev the plugin's revision
 * @param register_functions function to register the plugin's document functions
 * @param mimetypes a char array of mime types supported by the plugin
 */
#define PLUGIN_REGISTER(plugin_name, major, minor, rev, register_functions, mimetypes) \
  unsigned int plugin_version_major() { return major; } \
  unsigned int plugin_version_minor() { return minor; } \
  unsigned int plugin_version_revision() { return rev; } \
  unsigned int plugin_api_version() { return ZATHURA_API_VERSION; } \
  unsigned int plugin_abi_version() { return ZATHURA_ABI_VERSION; } \
  \
  void plugin_register(zathura_plugin_t* plugin) \
  { \
    if (plugin == NULL) { \
      return; \
    } \
    zathura_plugin_set_register_functions_function(plugin, register_functions); \
    static const char* mime_types[] = mimetypes; \
    for (size_t s = 0; s != sizeof(mime_types) / sizeof(const char*); ++s) { \
      zathura_plugin_add_mimetype(plugin, mime_types[s]); \
    } \
  } \

#define PLUGIN_MIMETYPES(...) __VA_ARGS__

struct zathura_document_functions_s
{
  /**
   * Opens a document
   */
  zathura_error_t (*document_open)(zathura_document_t* document);

  /**
   * Frees the document
   */
  zathura_error_t (*document_free)(zathura_document_t* document, zathura_document_data_t* data);

  /**
   * Generates the document index
   */
  girara_tree_node_t* (*document_index_generate)(zathura_document_t* document, zathura_document_data_t* data, zathura_error_t* error);

  /**
   * Save the document
   */
  zathura_error_t (*document_save_as)(zathura_document_t* document, zathura_document_data_t* data, const char* path);

  /**
   * Get list of attachments
   */
  girara_list_t* (*document_attachments_get)(zathura_document_t* document, zathura_document_data_t* data, zathura_error_t* error);

  /**
   * Save attachment to a file
   */
  zathura_error_t (*document_attachment_save)(zathura_document_t* document, zathura_document_data_t* data, const char* attachment, const char* file);

  /**
   * Get document information
   */
  char* (*document_meta_get)(zathura_document_t* document, zathura_document_data_t* data, zathura_document_meta_t info, zathura_error_t* error);

  /**
   * Gets the page object
   */
  zathura_error_t (*page_init)(zathura_page_t* page);

  /**
   * Free page
   */
  zathura_error_t (*page_clear)(zathura_page_t* page, zathura_page_data_t* data);

  /**
   * Search text
   */
  girara_list_t* (*page_search_text)(zathura_page_t* page, zathura_page_data_t* data, const char* text, zathura_error_t* error);

  /**
   * Get links on a page
   */
  girara_list_t* (*page_links_get)(zathura_page_t* page, zathura_page_data_t* data, zathura_error_t* error);

  /**
   * Get form fields
   */
  girara_list_t* (*page_form_fields_get)(zathura_page_t* page, zathura_page_data_t* data, zathura_error_t* error);

  /**
   * Get list of images
   */
  girara_list_t* (*page_images_get)(zathura_page_t* page, zathura_page_data_t* data, zathura_error_t* error);

  /**
   * Get the image
   */
  cairo_surface_t* (*page_image_get_cairo)(zathura_page_t* page, zathura_page_data_t* data, zathura_image_t* image, zathura_error_t* error);

  /**
   * Get text for selection
   */
  char* (*page_get_text)(zathura_page_t* page, zathura_page_data_t* data, zathura_rectangle_t rectangle, zathura_error_t* error);

  /**
   * Renders the page
   */
  zathura_image_buffer_t* (*page_render)(zathura_page_t* page, zathura_page_data_t* data, zathura_error_t* error);

  /**
   * Renders the page
   */
  zathura_error_t (*page_render_cairo)(zathura_page_t* page, zathura_page_data_t* data, cairo_t* cairo, bool printing);
};


#endif // PLUGIN_API_H
