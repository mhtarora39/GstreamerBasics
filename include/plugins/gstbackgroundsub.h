/* GStreamer
 * Copyright (C) 2023 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_BACKGROUNDSUB_H_
#define _GST_BACKGROUNDSUB_H_

#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"

G_BEGIN_DECLS

#define GST_TYPE_BACKGROUNDSUB   (gst_backgroundsub_get_type())
#define GST_BACKGROUNDSUB(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_BACKGROUNDSUB,GstBackgroundsub))
#define GST_BACKGROUNDSUB_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_BACKGROUNDSUB,GstBackgroundsubClass))
#define GST_IS_BACKGROUNDSUB(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_BACKGROUNDSUB))
#define GST_IS_BACKGROUNDSUB_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_BACKGROUNDSUB))

typedef struct _GstBackgroundsub GstBackgroundsub;
typedef struct _GstBackgroundsubClass GstBackgroundsubClass;

struct _GstBackgroundsub
{
  GstVideoFilter base_backgroundsub;

};

struct _GstBackgroundsubClass
{
  GstVideoFilterClass base_backgroundsub_class;
};

GType gst_backgroundsub_get_type (void);

G_END_DECLS

#endif
