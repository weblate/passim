/*
 * Copyright (C) 2023 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#include "config.h"

#include "passim-item.h"

/**
 * PassimItem:
 *
 * A shared item.
 */

typedef struct {
	gchar *hash;
	gchar *basename;
	guint32 max_age;
	guint32 share_limit;
	guint32 share_count;
	GFile *file;
	GDateTime *ctime;
} PassimItemPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(PassimItem, passim_item, G_TYPE_OBJECT)
#define GET_PRIVATE(o) (passim_item_get_instance_private(o))

/**
 * passim_item_get_hash:
 * @self: a #PassimItem
 *
 * Gets the file hash.
 *
 * Returns: the typically in SHA-256 lowercase form, or %NULL if unset
 *
 * Since: 0.1.0
 **/
const gchar *
passim_item_get_hash(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);
	return priv->hash;
}

/**
 * passim_item_set_hash:
 * @self: a #PassimItem
 * @hash: (nullable): the hash, typically in SHA-256 lowercase form
 *
 * Sets the file hash.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_hash(PassimItem *self, const gchar *hash)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));

	/* not changed */
	if (g_strcmp0(priv->hash, hash) == 0)
		return;

	g_free(priv->hash);
	priv->hash = g_strdup(hash);
}

/**
 * passim_item_get_basename:
 * @self: a #PassimItem
 *
 * Gets the basename of the file that was published.
 *
 * Returns: the test basename, or %NULL if unset
 *
 * Since: 0.1.0
 **/
const gchar *
passim_item_get_basename(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);
	return priv->basename;
}

/**
 * passim_item_set_basename:
 * @self: a #PassimItem
 * @basename: (nullable): the basename name
 *
 * Sets the basename of the file that was published.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_basename(PassimItem *self, const gchar *basename)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));

	/* not changed */
	if (g_strcmp0(priv->basename, basename) == 0)
		return;

	g_free(priv->basename);
	priv->basename = g_strdup(basename);
}

/**
 * passim_item_get_max_age:
 * @self: a #PassimItem
 *
 * Gets the maximum permitted file age.
 *
 * Returns: time in hours
 *
 * Since: 0.1.0
 **/
guint32
passim_item_get_max_age(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), 0);
	return priv->max_age;
}

/**
 * passim_item_set_max_age:
 * @self: a #PassimItem
 * @max_age: time in hours
 *
 * Sets the maximum permitted file age.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_max_age(PassimItem *self, guint32 max_age)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));
	priv->max_age = max_age;
}

/**
 * passim_item_get_share_limit:
 * @self: a #PassimItem
 *
 * Gets the maximum number of times that the file can be shared.
 *
 * Returns: share limit, or 0 if unset
 *
 * Since: 0.1.0
 **/
guint32
passim_item_get_share_limit(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), 0);
	return priv->share_limit;
}

/**
 * passim_item_set_share_limit:
 * @self: a #PassimItem
 * @share_limit: the share limit, or 0
 *
 * Sets the maximum number of times that the file can be shared.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_share_limit(PassimItem *self, guint32 share_limit)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));
	priv->share_limit = share_limit;
}

/**
 * passim_item_get_share_count:
 * @self: a #PassimItem
 *
 * Gets the current number of times the item has been shared to other machines.
 *
 * Returns: the count, or 0 if unset
 *
 * Since: 0.1.0
 **/
guint32
passim_item_get_share_count(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), 0);
	return priv->share_count;
}

/**
 * passim_item_set_share_count:
 * @self: a #PassimItem
 * @share_count: the count, or 0 to unset
 *
 * Sets the current number of times the item has been shared to other machines.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_share_count(PassimItem *self, guint32 share_count)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));
	priv->share_count = share_count;
}

/**
 * passim_item_get_file:
 * @self: a #PassimItem
 *
 * Gets the local file in the cache.
 *
 * Returns: (transfer none): a #GFile, or %NULL if unset
 *
 * Since: 0.1.0
 **/
GFile *
passim_item_get_file(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);
	return priv->file;
}

/**
 * passim_item_set_file:
 * @self: a #PassimItem
 * @file: (nullable): a #GFile
 *
 * Sets the local file in the cache.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_file(PassimItem *self, GFile *file)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));
	g_set_object(&priv->file, file);
}

/**
 * passim_item_get_ctime:
 * @self: a #PassimItem
 *
 * Gets the creation time of the file.
 *
 * Returns: (transfer none): the creation time, or %NULL if unset
 *
 * Since: 0.1.0
 **/
GDateTime *
passim_item_get_ctime(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);
	return priv->ctime;
}

/**
 * passim_item_set_ctime:
 * @self: a #PassimItem
 * @ctime: (nullable): a #GDateTime
 *
 * Sets the creation time of the file.
 *
 * Since: 0.1.0
 **/
void
passim_item_set_ctime(PassimItem *self, GDateTime *ctime)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_if_fail(PASSIM_IS_ITEM(self));

	/* not changed */
	if (priv->ctime == ctime)
		return;
	if (priv->ctime != NULL) {
		g_date_time_unref(priv->ctime);
		priv->ctime = NULL;
	}
	if (ctime != NULL)
		priv->ctime = g_date_time_ref(ctime);
}

static gchar *
passim_compute_checksum_for_filename(const gchar *filename, GError **error)
{
	gsize bufsz = 0;
	g_autofree gchar *buf = NULL;
	if (!g_file_get_contents(filename, &buf, &bufsz, error))
		return NULL;
	return g_compute_checksum_for_data(G_CHECKSUM_SHA256, (const guchar *)buf, bufsz);
}

/**
 * passim_item_load_filename:
 * @self: a #PassimItem
 * @filename: (not nullable): a filename with full path
 * @error: (nullable): optional return location for an error
 *
 * Loads the item from a file on disk.
 *
 * Since: 0.1.0
 **/
gboolean
passim_item_load_filename(PassimItem *self, const gchar *filename, GError **error)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_autoptr(GFile) file = NULL;
	g_autoptr(GFileInfo) info = NULL;

	g_return_val_if_fail(PASSIM_IS_ITEM(self), FALSE);
	g_return_val_if_fail(filename != NULL, FALSE);
	g_return_val_if_fail(error == NULL || *error == NULL, FALSE);

	/* set file */
	file = g_file_new_for_path(filename);
	passim_item_set_file(self, file);

	/* get ctime */
	info = g_file_query_info(file,
				 G_FILE_ATTRIBUTE_TIME_CREATED,
				 G_FILE_QUERY_INFO_NONE,
				 NULL,
				 error);
	if (info == NULL)
		return FALSE;
	priv->ctime = g_file_info_get_creation_date_time(info);

	/* if not already set */
	if (priv->basename == NULL)
		priv->basename = g_path_get_basename(filename);
	if (priv->hash == NULL) {
		priv->hash = passim_compute_checksum_for_filename(filename, error);
		if (priv->hash == NULL)
			return FALSE;
	}

	/* success */
	return TRUE;
}

/**
 * passim_item_to_variant:
 * @self: a #PassimItem
 *
 * Serialize the item data.
 *
 * Returns: the serialized data, or %NULL for error
 *
 * Since: 0.1.0
 **/
GVariant *
passim_item_to_variant(PassimItem *self)
{
	GVariantBuilder builder;
	PassimItemPrivate *priv = GET_PRIVATE(self);

	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);

	g_variant_builder_init(&builder, G_VARIANT_TYPE_VARDICT);
	g_variant_builder_add(&builder, "{sv}", "filename", g_variant_new_string(priv->basename));
	g_variant_builder_add(&builder, "{sv}", "hash", g_variant_new_string(priv->hash));
	g_variant_builder_add(&builder, "{sv}", "max-age", g_variant_new_uint32(priv->max_age));
	g_variant_builder_add(&builder,
			      "{sv}",
			      "share-limit",
			      g_variant_new_uint32(priv->share_limit));
	g_variant_builder_add(&builder,
			      "{sv}",
			      "share-count",
			      g_variant_new_uint32(priv->share_count));
	return g_variant_builder_end(&builder);
}

/**
 * passim_item_from_variant:
 * @value: (not nullable): the serialized data
 *
 * Creates a new item using serialized data.
 *
 * Returns: (transfer full): a new #PassimItem, or %NULL if @value was invalid
 *
 * Since: 0.1.0
 **/
PassimItem *
passim_item_from_variant(GVariant *variant)
{
	GVariant *value;
	const gchar *key;
	g_autoptr(GVariantIter) iter = NULL;
	g_autoptr(PassimItem) self = passim_item_new();
	PassimItemPrivate *priv = GET_PRIVATE(self);

	g_return_val_if_fail(variant != NULL, NULL);

	g_variant_get(variant, "a{sv}", &iter);
	while (g_variant_iter_next(iter, "{&sv}", &key, &value)) {
		if (g_strcmp0(key, "filename") == 0)
			priv->basename = g_variant_dup_string(value, NULL);
		if (g_strcmp0(key, "hash") == 0)
			priv->hash = g_variant_dup_string(value, NULL);
		if (g_strcmp0(key, "max-age") == 0)
			priv->max_age = g_variant_get_uint32(value);
		if (g_strcmp0(key, "share-limit") == 0)
			priv->share_limit = g_variant_get_uint32(value);
		if (g_strcmp0(key, "share-count") == 0)
			priv->share_count = g_variant_get_uint32(value);
		g_variant_unref(value);
	}
	return g_steal_pointer(&self);
}

/**
 * passim_item_to_string:
 * @self: a #PassimItem
 *
 * Builds a text representation of the object.
 *
 * Returns: text, or %NULL for invalid
 *
 * Since: 0.1.0
 **/
gchar *
passim_item_to_string(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	g_return_val_if_fail(PASSIM_IS_ITEM(self), NULL);
	return g_strdup_printf("%s %s (max-age: %u, share-count: %u, share-limit: %u)",
			       priv->hash,
			       priv->basename,
			       priv->max_age,
			       priv->share_count,
			       priv->share_limit);
}

static void
passim_item_init(PassimItem *self)
{
	PassimItemPrivate *priv = GET_PRIVATE(self);
	priv->max_age = 24 * 60 * 60;
	priv->share_limit = 5;
}

static void
passim_item_finalize(GObject *object)
{
	PassimItem *self = PASSIM_ITEM(object);
	PassimItemPrivate *priv = GET_PRIVATE(self);

	if (priv->file != NULL)
		g_object_unref(priv->file);
	if (priv->ctime != NULL)
		g_date_time_unref(priv->ctime);
	g_free(priv->hash);
	g_free(priv->basename);

	G_OBJECT_CLASS(passim_item_parent_class)->finalize(object);
}

static void
passim_item_class_init(PassimItemClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->finalize = passim_item_finalize;
}

/**
 * passim_item_new:
 *
 * Creates a new item.
 *
 * Returns: a new #PassimItem
 *
 * Since: 0.1.0
 **/
PassimItem *
passim_item_new(void)
{
	PassimItem *self;
	self = g_object_new(PASSIM_TYPE_ITEM, NULL);
	return PASSIM_ITEM(self);
}