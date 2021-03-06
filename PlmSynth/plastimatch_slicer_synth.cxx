/*==========================================================================

  Copyright (c) Massachusetts General Hospital, Boston, MA, USA. All Rights Reserved.
 
  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Gregory C. Sharp, Massachusetts General Hospital
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Natural Sciences and Engineering Research Council
  of Canada.

==========================================================================*/

#include "plm_config.h"
#include "plastimatch_slicer_synthCLP.h"

#include "itk_image.h"
#include "itk_image_save.h"
#include "plm_image.h"
#include "rt_study.h"
#include "rtss.h"
#include "synthetic_mha.h"

int 
main (int argc, char * argv [])
{
  PARSE_ARGS;

  Synthetic_mha_parms sm_parms;
  if (plmslc_dim.size() >= 3) {
    sm_parms.dim[0] = plmslc_dim[0];
    sm_parms.dim[1] = plmslc_dim[1];
    sm_parms.dim[2] = plmslc_dim[2];
  } else if (plmslc_dim.size() >= 1) {
    sm_parms.dim[0] = plmslc_dim[0];
    sm_parms.dim[1] = plmslc_dim[0];
    sm_parms.dim[2] = plmslc_dim[0];
  }
  if (plmslc_origin.size() >= 3) {
    sm_parms.origin[0] = plmslc_origin[0];
    sm_parms.origin[1] = plmslc_origin[1];
    sm_parms.origin[2] = plmslc_origin[2];
  } else if (plmslc_origin.size() >= 1) {
    sm_parms.origin[0] = plmslc_origin[0];
    sm_parms.origin[1] = plmslc_origin[0];
    sm_parms.origin[2] = plmslc_origin[0];
  }
  if (plmslc_spacing.size() >= 3) {
    sm_parms.spacing[0] = plmslc_spacing[0];
    sm_parms.spacing[1] = plmslc_spacing[1];
    sm_parms.spacing[2] = plmslc_spacing[2];
  } else if (plmslc_spacing.size() >= 1) {
    sm_parms.spacing[0] = plmslc_spacing[0];
    sm_parms.spacing[1] = plmslc_spacing[0];
    sm_parms.spacing[2] = plmslc_spacing[0];
  }

  /* Pattern options */
  if (plmslc_pattern == "Gauss") {
    sm_parms.pattern = PATTERN_GAUSS;
  } else if (plmslc_pattern == "Rectangle") {
    sm_parms.pattern = PATTERN_RECT;
  } else if (plmslc_pattern == "Sphere") {
    sm_parms.pattern = PATTERN_SPHERE;
  } 
	
  sm_parms.foreground = plmslc_foreground;
  sm_parms.background = plmslc_background;

  /* Gauss options */
  if (plmslc_gausscenter.size() >= 3) {
    sm_parms.gauss_center[0] = plmslc_gausscenter[0];
    sm_parms.gauss_center[1] = plmslc_gausscenter[1];
    sm_parms.gauss_center[2] = plmslc_gausscenter[2];
  } else if (plmslc_gausscenter.size() >= 1) {
    sm_parms.gauss_center[0] = plmslc_gausscenter[0];
    sm_parms.gauss_center[1] = plmslc_gausscenter[0];
    sm_parms.gauss_center[2] = plmslc_gausscenter[0];
  }
  if (plmslc_gausswidth.size() >= 3) {
    sm_parms.gauss_std[0] = plmslc_gausswidth[0];
    sm_parms.gauss_std[1] = plmslc_gausswidth[1];
    sm_parms.gauss_std[2] = plmslc_gausswidth[2];
  } else if (plmslc_gausswidth.size() >= 1) {
    sm_parms.gauss_std[0] = plmslc_gausswidth[0];
    sm_parms.gauss_std[1] = plmslc_gausswidth[0];
    sm_parms.gauss_std[2] = plmslc_gausswidth[0];
  }

  /* Rect options */
  if (plmslc_rectsize.size() >= 6) {
    sm_parms.rect_size[0] = plmslc_rectsize[0];
    sm_parms.rect_size[1] = plmslc_rectsize[1];
    sm_parms.rect_size[2] = plmslc_rectsize[2];
    sm_parms.rect_size[3] = plmslc_rectsize[3];
    sm_parms.rect_size[4] = plmslc_rectsize[4];
    sm_parms.rect_size[5] = plmslc_rectsize[5];
  } else if (plmslc_rectsize.size() >= 3) {
    sm_parms.rect_size[0] = - 0.5 * plmslc_rectsize[0];
    sm_parms.rect_size[2] = - 0.5 * plmslc_rectsize[1];
    sm_parms.rect_size[4] = - 0.5 * plmslc_rectsize[2];
    sm_parms.rect_size[1] = - sm_parms.rect_size[0];
    sm_parms.rect_size[3] = - sm_parms.rect_size[2];
    sm_parms.rect_size[5] = - sm_parms.rect_size[4];
  }
  else if (plmslc_rectsize.size() >= 1) {
    sm_parms.rect_size[0] = - 0.5 * plmslc_rectsize[0];
    sm_parms.rect_size[1] = - sm_parms.rect_size[0];
    sm_parms.rect_size[2] = + sm_parms.rect_size[0];
    sm_parms.rect_size[3] = - sm_parms.rect_size[0];
    sm_parms.rect_size[4] = + sm_parms.rect_size[0];
    sm_parms.rect_size[5] = - sm_parms.rect_size[0];
  }

  /* Sphere options */
  if (plmslc_spherecenter.size() >= 3) {
    sm_parms.sphere_center[0] = plmslc_spherecenter[0];
    sm_parms.sphere_center[1] = plmslc_spherecenter[1];
    sm_parms.sphere_center[2] = plmslc_spherecenter[2];
  } else if (plmslc_spherecenter.size() >= 1) {
    sm_parms.sphere_center[0] = plmslc_spherecenter[0];
    sm_parms.sphere_center[1] = plmslc_spherecenter[0];
    sm_parms.sphere_center[2] = plmslc_spherecenter[0];
  }
  if (plmslc_spheresize.size() >= 3) {
    sm_parms.sphere_radius[0] = plmslc_spheresize[0];
    sm_parms.sphere_radius[1] = plmslc_spheresize[1];
    sm_parms.sphere_radius[2] = plmslc_spheresize[2];
  } else if (plmslc_spheresize.size() >= 1) {
    sm_parms.sphere_radius[0] = plmslc_spheresize[0];
    sm_parms.sphere_radius[1] = plmslc_spheresize[0];
    sm_parms.sphere_radius[2] = plmslc_spheresize[0];
  }

  /* Create Volume 1 */
  /* Also write out dose and structure set image if requested */
  if (plmslc_output_one != "" && plmslc_output_one != "None") {
    Rt_study rtds;

    if (plmslc_output_dosemha != "" && plmslc_output_dosemha != "None") {
      sm_parms.m_want_dose_img = true;
    }
    if (plmslc_output_ssmha != "" && plmslc_output_ssmha != "None") {
      sm_parms.m_want_ss_img = true;
    }

    synthetic_mha (&rtds, &sm_parms);
    FloatImageType::Pointer img = rtds.get_image()->itk_float();
    itk_image_save_float (img, plmslc_output_one.c_str());

    if (plmslc_output_dosemha != "" && plmslc_output_dosemha != "None") {
      rtds.get_dose()->save_image (plmslc_output_dosemha.c_str());
    }

    if (plmslc_output_ssmha != "" && plmslc_output_ssmha != "None") {
      itk_image_save (rtds.get_segmentation()->get_structure_image (1),
                      plmslc_output_ssmha.c_str());
    }
  }

  /* Create Volume 2 */
  if (plmslc_output_two != "" && plmslc_output_two != "None") {

    float xlat[3] = { 0.f, 0.f, 0.f };
    if (plmslc_vol2xlat.size() >= 1) {
      xlat[0] = plmslc_vol2xlat[0];
    }
    if (plmslc_vol2xlat.size() >= 3) {
      xlat[1] = plmslc_vol2xlat[1];
      xlat[2] = plmslc_vol2xlat[2];
    }

    /* Translate volume */
    sm_parms.rect_size[0] += xlat[0];
    sm_parms.rect_size[1] += xlat[0];
    sm_parms.rect_size[2] += xlat[1];
    sm_parms.rect_size[3] += xlat[1];
    sm_parms.rect_size[4] += xlat[2];
    sm_parms.rect_size[5] += xlat[2];
    sm_parms.sphere_center[0] += xlat[0];
    sm_parms.sphere_center[1] += xlat[1];
    sm_parms.sphere_center[2] += xlat[2];
    sm_parms.gauss_center[0] += xlat[0];
    sm_parms.gauss_center[1] += xlat[1];
    sm_parms.gauss_center[2] += xlat[2];

    /* Only save the image */
    Rt_study rtds;
    synthetic_mha (&rtds, &sm_parms);
    FloatImageType::Pointer img = rtds.get_image()->itk_float();
    itk_image_save_float (img, plmslc_output_two.c_str());
  }


  return EXIT_SUCCESS;
}
